//
// Created by crist on 11/11/2025.
//

#include "BaseMemory.h"

#include <algorithm>
#include <ostream>

bool ProcessDummy::operator()(const std::pair<int, Process> &a, const std::pair<int, Process> &b) const {
    return a.first < b.first;
}

void BaseMemory::deallocate(const Process &process) {
    for (auto it = memory.begin(); it != memory.end(); ++it) {
        if (it->second.getPid() == process.getPid()) {
            memory.erase(it);
            return;
        }
    }
}

bool BaseMemory::hasProcess(const Process &process) const {
    // Busca un proceso en la memoria por su PID
    return std::ranges::any_of(memory.begin(), memory.end(), [&process](const std::pair<int, Process> &item) {
        return item.second.getPid() == process.getPid();
    });
}

std::ostream &operator<<(std::ostream &os, const BaseMemory &baseMemory) {
    auto memory = baseMemory.memory;
    if (memory.empty()) {
        os << "[0, " << baseMemory.maxMemory << ", 0]";
        return os;
    }
    auto it = memory.begin();
    int lastEnd = 0;
    while (it != memory.end()) {
        if (it->first > lastEnd) {
            os << " [0, "
                    << (it->first - lastEnd) << ", 0] ";
        }
        lastEnd = it->first + it->second.getMemory();
        os << (it++)->second;
        if (it != memory.end()) {
            os << " ";
        } else if (lastEnd < baseMemory.maxMemory) {
            os << " [0, " << (baseMemory.maxMemory - lastEnd) << ", 0]";
        }
    }
    return os;
}
