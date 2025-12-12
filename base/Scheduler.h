//
// Created by crist on 11/11/2025.
//

#ifndef PROCESSSCHEDULER_SCHEDULER_H
#define PROCESSSCHEDULER_SCHEDULER_H
#include <list>
#include <memory>
#include <ostream>
#include <queue>
#include <utility>

#include "../memory/BaseMemory.h"
#include "Process.h"

enum StepType { NEW, BLOCKED, UNLOCKED };

struct Step {
  Process process;
  StepType type;
  Process current;
  std::list<Process> queue;
  std::list<MemoryBlock> memory;

  Step() : process(128, 10), current(128, 10) {}
};

class Scheduler {
  std::queue<Process> processes;
  std::unique_ptr<Process> blocked = nullptr;
  int maxMemory;
  int maxQuantum;
  int systemQuantum;
  std::shared_ptr<BaseMemory> memoryManager;
  std::pair<StepType, Process> addProcess();
  std::list<Process> normalize() const;

 public:
  Scheduler(const int maxMemory, const int maxQuantum, std::shared_ptr<BaseMemory> memory,
            const int pQ)
      : maxMemory(maxMemory),
        maxQuantum(maxQuantum),
        systemQuantum(pQ),
        memoryManager(memory) {};
  Step schedule();
  void clear();

  friend std::ostream& operator<<(std::ostream&, const Scheduler&);
};

std::ostream& operator<<(std::ostream&, const Step&);

#endif  // PROCESSSCHEDULER_SCHEDULER_H
