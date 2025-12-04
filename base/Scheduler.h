//
// Created by crist on 11/11/2025.
//

#ifndef PROCESSSCHEDULER_SCHEDULER_H
#define PROCESSSCHEDULER_SCHEDULER_H
#include <ostream>
#include <queue>

#include "../memory/BaseMemory.h"
#include "Process.h"

class Scheduler {
    std::queue<Process> processes;
    Process* blocked = nullptr;
    int maxMemory;
    int maxQuantum;
    int systemQuantum;
    BaseMemory* memoryManager;
    void addProcess(const Process& process);

   public:
    Scheduler(const int maxMemory, const int maxQuantum, BaseMemory* memory, const int pQ)
        : maxMemory(maxMemory), maxQuantum(maxQuantum), systemQuantum(pQ), memoryManager(memory) {};
    [[noreturn]] void schedule();

    friend std::ostream& operator<<(std::ostream&, const Scheduler&);
};

#endif  // PROCESSSCHEDULER_SCHEDULER_H
