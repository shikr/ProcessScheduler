//
// Created by crist on 11/11/2025.
//

#include "Scheduler.h"

#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

static int QUANTUM = 1000;

void Scheduler::addProcess(const Process& process) {
    // allocate regresa verdadero cuando el proceso se puede ajustar a la memoria
    if (memoryManager->allocate(process)) {
        std::cout << std::endl << "Nuevo: " << process << std::endl;
        // si el proceso se agrego a la memoria, tambien se agrega a la cola de
        // procesos
        processes.push(process);
    } else {
        // si el proceso no se pudo ajustar a la memoria, se bloquea
        std::cout << std::endl << "Bloqueado: " << process << std::endl;
        blocked = new Process(process);
    }
}

[[noreturn]]
void Scheduler::schedule() {
    // muestra la memoria vacia
    std::cout << std::endl << *memoryManager << std::endl;
    while (true) {
        // calcula el tiempo en el que se acabara el quantum
        auto end = std::chrono::system_clock::now() + std::chrono::milliseconds(QUANTUM);
        // Se bloquea mientras el proceso se ejecute un quantum
        std::this_thread::sleep_until(end);
        if (blocked == nullptr)
            addProcess(Process(maxMemory, maxQuantum));
        else if (memoryManager->allocate(*blocked)) {
            std::cout << std::endl << "Desbloqueado: " << *blocked << std::endl;
            processes.push(*blocked);
            blocked = nullptr;
        } else {
            std::cout << std::endl << "Bloqueado: " << *blocked << std::endl;
        }
        Process curr = processes.front();
        std::cout << "Memoria inicial: " << *memoryManager << std::endl;
        std::cout << "Cola: " << *this << std::endl;
        std::cout << "Ejecutandose: " << curr << std::endl;
        // ejecuta el proceso actual (le resta los quantum)
        curr.execute(systemQuantum);
        // elimina el proceso de la cola
        processes.pop();
        // si el proceso sigue vivo lo agrega al final de la cola y lo actualiza en
        // la memoria
        if (curr.isAlive()) {
            processes.push(curr);
            memoryManager->reallocate(curr);
        } else {
            // al terminar el proceso, lo elimina de la memoria
            memoryManager->deallocate(curr);
        }
        std::cout << "Memoria final: " << *memoryManager << std::endl;
        if (!processes.empty()) std::cout << "Cola final: " << *this << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Scheduler& obj) {
    std::queue<Process> processes = obj.processes;

    while (!processes.empty()) {
        os << processes.front() << " ";
        processes.pop();
    }

    return os;
}
