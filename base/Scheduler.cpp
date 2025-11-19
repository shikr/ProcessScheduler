//
// Created by crist on 11/11/2025.
//

#include "Scheduler.h"

#include <chrono>
#include <iostream>
#include <ostream>

#include "../util/random.h"

static int QUANTUM = 1000;

// Genera el tiempo para agregar un nuevo proceso
static std::chrono::time_point<std::chrono::system_clock> genNextProcessTime() {
    // Al tiempo actual, se le suma un tiempo aleatorio en milisegundos generado
    // por la funcion random
    return std::chrono::system_clock::now() +
           std::chrono::milliseconds(random(1300, 1600));
}

void Scheduler::addProcess(const Process& process) {
    // allocate regresa verdadero cuando el proceso se puede ajustar a la memoria
    if (memoryManager->allocate(process)) {
        std::cout << std::endl << "Nuevo: " << process << std::endl;
        std::cout << *memoryManager << std::endl;
        // si el proceso se agrego a la memoria, tambien se agrega a la cola de
        // procesos
        processes.push(process);
    } else {
        // si el proceso no se pudo ajustar a la memoria, se agrega a una nueva cola
        // de espera
        blockedProcesses.push(process);
    }
}

[[noreturn]]
void Scheduler::schedule() {
    // genera el tiempo en el que se va a crear un nuevo proceso
    auto next = genNextProcessTime();
    // muestra la memoria vacia
    std::cout << std::endl << *memoryManager << std::endl;
    // agrega un nuevo proceso
    addProcess(Process(maxMemory, maxQuantum));
    while (true) {
        // calcula el tiempo en el que se acabara el quantum
        auto end = std::chrono::system_clock::now() + std::chrono::milliseconds(QUANTUM);
        Process curr = processes.front();
        std::cout << std::endl << "Atendiendo: " << curr << std::endl;
        // Se bloquea mientras el proceso se ejecute un quantum
        while (std::chrono::system_clock::now() < end) {
            // si mientras se esta ejecutando un quantum, es tiempo de generar otro
            // proceso entonces lo hace y reinicia el contador para generar un nuevo
            // proceso
            if (std::chrono::system_clock::now() > next) {
                addProcess(Process(maxMemory, maxQuantum));
                next = genNextProcessTime();
            }
        }
        // ejecuta el proceso actual (le resta los quantum)
        curr.execute();
        // elimina el proceso de la cola
        processes.pop();
        // Si solo queda el proceso actual y este ha terminado, se agrega uno nuevo
        // antes de dejar la memoría vacía
        if (processes.empty() && !curr.isAlive())
            addProcess(Process(maxMemory, maxQuantum));
        // std::cout << std::endl << "Atendido: " << curr << std::endl;
        // si el proceso sigue vivo lo agrega al final de la cola y lo actualiza en
        // la memoria
        if (curr.isAlive()) {
            processes.push(curr);
            memoryManager->reallocate(curr);
        } else {
            // al terminar el proceso, lo elimina de la memoria
            memoryManager->deallocate(curr);
            // Intentar agregar procesos bloqueados
            const auto blockedSize = blockedProcesses.size();
            // Recorre la cola de bloqueados por indices, para hacerlo solo una vez
            for (int i = 0; i < blockedSize; ++i) {
                Process blocked = blockedProcesses.front();
                blockedProcesses.pop();
                // intenta colocar el proceso en la memoria
                if (memoryManager->allocate(blocked)) {
                    // si se ajusto a la memoria, se desbloquea y se agrega a la cola de
                    // procesos
                    std::cout << std::endl << "Desbloqueado: " << blocked << std::endl;
                    processes.push(blocked);
                } else {
                    // si no se pudo ajustar, se queda en la cola de bloqueados
                    blockedProcesses.push(blocked);
                }
            }
        }
        std::cout << std::endl << *memoryManager << std::endl;
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
