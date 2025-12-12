//
// Created by crist on 11/11/2025.
//

#include "BaseMemory.h"

#include <algorithm>
#include <list>
#include <memory>
#include <ostream>
#include <ranges>

bool ProcessDummy::operator()(const std::pair<int, Process>& a,
                              const std::pair<int, Process>& b) const {
  return a.first < b.first;
}

BaseMemory::BaseMemory(const int m) : maxMemory(m) {}

void BaseMemory::deallocate(const Process& process) {
  for (auto it = memory.begin(); it != memory.end(); ++it) {
    if (it->second.getPid() == process.getPid()) {
      memory.erase(it);
      return;
    }
  }
}

void BaseMemory::reallocate(const Process& process) {
  for (auto it = memory.begin(); it != memory.end(); ++it) {
    if (it->second.getPid() == process.getPid()) {
      Process updatedProcess = process;
      memory.erase(it);
      memory.insert({it->first, updatedProcess});
      return;
    }
  }
}

void BaseMemory::clear() { memory.clear(); }

bool BaseMemory::hasProcess(const Process& process) const {
  // Busca un proceso en la memoria por su PID
  return std::ranges::any_of(memory.begin(), memory.end(),
                             [&process](const std::pair<int, Process>& item) {
                               return item.second.getPid() == process.getPid();
                             });
}

std::list<MemoryBlock> BaseMemory::normalize() const {
  std::list<MemoryBlock> blocks;

  int current = 0;
  for (const auto& [start, process] : memory) {
    if (start > current) {
      blocks.push_back({
          .start = current,
          .size = start - current,
          .isFree = true,
          .process = nullptr,
      });
    }

    blocks.push_back({
        .start = start,
        .size = process.getMemory(),
        .isFree = false,
        .process = std::make_shared<Process>(process),
    });

    current = start + process.getMemory();
  }

  if (current < maxMemory) {
    blocks.push_back({
        .start = current,
        .size = maxMemory - current,
        .isFree = true,
        .process = nullptr,
    });
  }

  return blocks;
}

std::ostream& operator<<(std::ostream& os, const BaseMemory& baseMemory) {
  auto memory = baseMemory.normalize();
  bool first = true;

  for (const auto& block : memory) {
    if (!first) os << " ";
    first = false;
    os << block;
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const MemoryBlock& block) {
  if (block.isFree)
    os << "[0, " << block.size << ", 0]";
  else
    os << *block.process;

  return os;
}
