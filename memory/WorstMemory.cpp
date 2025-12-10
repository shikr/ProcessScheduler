//
// Created by crist on 11/11/2025.
//

#include "WorstMemory.h"

class Process;

WorstMemory::WorstMemory(const int m) : BaseMemory(m) {}

bool WorstMemory::allocate(const Process& process) {
  int worstStart = -1;
  int worstSize = -1;
  int lastEnd = 0;

  for (const auto& [start, proc] : memory) {
    int gapSize = start - lastEnd;
    if (gapSize >= process.getMemory() && gapSize > worstSize) {
      worstSize = gapSize;
      worstStart = lastEnd;
    }
    lastEnd = start + proc.getMemory();
  }

  // Revisa el espacio al final de la memoria
  if (maxMemory - lastEnd >= process.getMemory() && (maxMemory - lastEnd) > worstSize) {
    worstStart = lastEnd;
  }

  if (worstStart != -1) {
    memory.insert({worstStart, process});
    return true;
  }
  return false;
}
