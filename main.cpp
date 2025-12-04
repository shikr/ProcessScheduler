#include "base/Scheduler.h"
#include "memory/FirstMemory.h"
#include <iostream>

#include "memory/BestMemory.h"
#include "memory/WorstMemory.h"

constexpr int MAX_MEMORY = 2048;
constexpr int MAX_QUANTUM = 5;

int main() {
    int choice, memorySize, maxMemory, maxQuantum, systemQuantum;
    BaseMemory *memoryManager;
    std::cout << "1. 8192" << std::endl;
    std::cout << "2. 4096" << std::endl;
    std::cout << "3. 1024" << std::endl;
    std::cout << "Seleccione un tamaño de memoria (1-3): ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            memorySize = 8192;
            break;
        case 2:
            memorySize = 4096;
            break;
        case 3:
            memorySize = 1024;
            break;
        default:
            return 1;
    }

    std::cout << "1. Primer Ajuste" << std::endl;
    std::cout << "2. Mejor Ajuste" << std::endl;
    std::cout << "3. Peor Ajuste" << std::endl;
    std::cout << "Seleccione un metodo de gestion de memoria (1-3): ";
    std::cin >> choice;

    std::cout << "Tamaño de maximo de memoria por proceso: ";
    std::cin >> maxMemory;
    std::cout << "Quantum maximo por proceso: ";
    std::cin >> maxQuantum;
    std::cout << "Quantum del sistema: ";
    std::cin >> systemQuantum;
    switch (choice) {
        case 1:
            memoryManager = new FirstMemory(memorySize);
            break;
        case 2:
            memoryManager = new BestMemory(memorySize);
            break;
        case 3:
            memoryManager = new WorstMemory(memorySize);
            break;
        default:
            return 1;
    }

    Scheduler scheduler(maxMemory, maxQuantum, memoryManager, systemQuantum);
    scheduler.schedule();
}