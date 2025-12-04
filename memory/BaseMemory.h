//
// Created by crist on 11/11/2025.
//

#ifndef PROCESSSCHEDULER_BASEMEMORY_H
#define PROCESSSCHEDULER_BASEMEMORY_H
#include <set>

#include "../base/Process.h"

struct ProcessDummy {
    bool operator()(const std::pair<int, Process> &a, const std::pair<int, Process> &b) const;
};

class BaseMemory {
protected:
    int maxMemory = 4096;
    std::set<std::pair<int, Process>, ProcessDummy> memory;

public:
    explicit BaseMemory(int);
    virtual ~BaseMemory() = default;

    virtual bool allocate(const Process &process) = 0;

    void deallocate(const Process &process);

    void reallocate(const Process &process);

    [[nodiscard]] bool hasProcess(const Process &process) const;

    friend std::ostream &operator<<(std::ostream &os, const BaseMemory &baseMemory);
};


#endif //PROCESSSCHEDULER_BASEMEMORY_H
