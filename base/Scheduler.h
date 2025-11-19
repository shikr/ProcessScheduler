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
    std::queue<Process> blockedProcesses;
    int maxMemory;
    int maxQuantum;
    BaseMemory* memoryManager;
    void addProcess(const Process& process);

   public:
    Scheduler(const int maxMemory, const int maxQuantum, BaseMemory* memory)
        : maxMemory(maxMemory), maxQuantum(maxQuantum), memoryManager(memory) {};
    [[noreturn]] void schedule();

    friend std::ostream& operator<<(std::ostream&, const Scheduler&);
};

#endif  // PROCESSSCHEDULER_SCHEDULER_H
