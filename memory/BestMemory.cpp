//
// Created by crist on 11/11/2025.
//

#include "BestMemory.h"

bool BestMemory::allocate(const Process &process) {
    int bestStart = -1;
    int bestSize = maxMemory + 1;
    int lastEnd = 0;

    for (const auto& [start, proc] : memory) {
        int gapSize = start - lastEnd;
        if (gapSize >= process.getMemory() && gapSize < bestSize) {
            bestSize = gapSize;
            bestStart = lastEnd;
        }
        lastEnd = start + proc.getMemory();
    }

    // Revisa el espacio al final de la memoria
    if (maxMemory - lastEnd >= process.getMemory() && (maxMemory - lastEnd) < bestSize) {
        bestStart = lastEnd;
    }

    if (bestStart != -1) {
        memory.insert({bestStart, process});
        return true;
    }
    return false;
}