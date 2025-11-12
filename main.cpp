#include "base/Scheduler.h"
#include "memory/FirstMemory.h"
#include <iostream>

#include "memory/BestMemory.h"
#include "memory/WorstMemory.h"

constexpr int MAX_MEMORY = 2048;
constexpr int MAX_QUANTUM = 5;

int main() {
    int choice;
    BaseMemory *memoryManager;
    std::cout << "1. Primer Ajuste" << std::endl;
    std::cout << "2. Mejor Ajuste" << std::endl;
    std::cout << "3. Peor Ajuste" << std::endl;
    std::cout << "Seleccione un metodo de gestion de memoria (1-3): ";
    std::cin >> choice;
    switch (choice) {
        case 1:
            memoryManager = new FirstMemory();
            break;
        case 2:
            memoryManager = new BestMemory();
            break;
        case 3:
            memoryManager = new WorstMemory();
            break;
        default:
            return 1;
    }

    Scheduler scheduler(MAX_MEMORY, MAX_QUANTUM, memoryManager);
    scheduler.schedule();
}