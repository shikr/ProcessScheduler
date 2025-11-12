//
// Created by crist on 11/11/2025.
//

#ifndef PROCESSSCHEDULER_SCHEDULER_H
#define PROCESSSCHEDULER_SCHEDULER_H
#include <queue>
#include "Process.h"
#include "../memory/BaseMemory.h"


class Scheduler {
    std::queue<Process> processes;
    int maxMemory;
    int maxQuantum;
    BaseMemory *memoryManager;
    void addProcess(const Process& process);

public:
    Scheduler(const int maxMemory, const int maxQuantum, BaseMemory* memory) : maxMemory(maxMemory), maxQuantum(maxQuantum), memoryManager(memory) {};
    [[noreturn]] void schedule();
};


#endif //PROCESSSCHEDULER_SCHEDULER_H