//
// Created by crist on 11/11/2025.
//

#include "Scheduler.h"
#include <iostream>
#include <chrono>
#include "../util/random.h"

static int QUANTUM = 1500;
static int MEMORY = 4096;

// Genera el tiempo para agregar un nuevo proceso
static std::chrono::time_point<std::chrono::system_clock> genNextProcessTime() {
    return std::chrono::system_clock::now() + std::chrono::milliseconds(random(350, 1000));
}

void Scheduler::addProcess(const Process& process) {
    std::cout << "Nuevo: " << process << " ";
    processes.push(process);
}

[[noreturn]]
void Scheduler::schedule() {
    auto next = genNextProcessTime();
    while (true) {
        if (processes.empty())
            addProcess(Process(maxMemory, maxQuantum));
        auto end = std::chrono::system_clock::now() + std::chrono::milliseconds(QUANTUM);
        Process curr = processes.front();
        curr.execute();
        processes.pop();
        // Se bloquea mientras el proceso se ejecute un quantum
        while (std::chrono::system_clock::now() < end) {
            if (std::chrono::system_clock::now() > next) {
                addProcess(Process(maxMemory, maxQuantum));
                next = genNextProcessTime();
            }
        }
        if (curr.isAlive()) processes.push(curr);
        else std::cout << std::endl << "Finalizado: " << curr << std::endl;
    }
}