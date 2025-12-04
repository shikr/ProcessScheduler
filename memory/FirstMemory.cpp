//
// Created by crist on 11/11/2025.
//

#include "FirstMemory.h"

FirstMemory::FirstMemory(const int m) : BaseMemory(m) {}

bool FirstMemory::allocate(const Process &process) {
    int lastEnd = 0;
    for (const auto& [start, proc] : memory) {
        if (start - lastEnd >= process.getMemory()) {
            memory.insert({lastEnd, process});
            return true;
        }
        lastEnd = start + proc.getMemory();
    }
    if (maxMemory - lastEnd >= process.getMemory()) {
        memory.insert({lastEnd, process});
        return true;
    }
    return false;
}