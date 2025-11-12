//
// Created by crist on 11/11/2025.
//

#include "Scheduler.h"
#include <iostream>
#include <chrono>
#include "../util/random.h"

static int QUANTUM = 750;

// Genera el tiempo para agregar un nuevo proceso
static std::chrono::time_point<std::chrono::system_clock> genNextProcessTime() {
    return std::chrono::system_clock::now() + std::chrono::milliseconds(random(1300, 1600));
}

void Scheduler::addProcess(const Process &process) {
    if (memoryManager->allocate(process)) {
        std::cout << std::endl << "Nuevo: " << process << std::endl;
        std::cout << *memoryManager << std::endl;
        processes.push(process);
    }
}

[[noreturn]]
void Scheduler::schedule() {
    auto next = genNextProcessTime();
    std::cout << std::endl << *memoryManager << std::endl;
    while (true) {
        if (processes.empty())
            addProcess(Process(maxMemory, maxQuantum));
        auto end = std::chrono::system_clock::now() + std::chrono::milliseconds(QUANTUM);
        Process curr = processes.front();
        // Se bloquea mientras el proceso se ejecute un quantum
        while (std::chrono::system_clock::now() < end) {
            if (std::chrono::system_clock::now() > next) {
                addProcess(Process(maxMemory, maxQuantum));
                next = genNextProcessTime();
            }
        }
        curr.execute();
        processes.pop();
        std::cout << std::endl << "Atendido: " << curr << std::endl;
        if (curr.isAlive()) {
            processes.push(curr);
            memoryManager->reallocate(curr);
        }
        else memoryManager->deallocate(curr);
        std::cout << *memoryManager << std::endl;
    }
}
