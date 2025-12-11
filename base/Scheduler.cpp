//
// Created by crist on 11/11/2025.
//

#include "Scheduler.h"

#include <iostream>
#include <list>
#include <memory>
#include <ostream>

#include "Process.h"

static int QUANTUM = 1000;

std::pair<StepType, Process> Scheduler::addProcess() {
  const auto process = Process(maxMemory, maxQuantum);
  // allocate regresa verdadero cuando el proceso se puede ajustar a la memoria
  if (memoryManager->allocate(process)) {
    // si el proceso se agrego a la memoria, tambien se agrega a la cola de
    // procesos
    processes.push(process);
    return {StepType::NEW, process};
  } else {
    // si el proceso no se pudo ajustar a la memoria, se bloquea
    blocked = std::make_unique<Process>(process);
    return {StepType::BLOCKED, process};
  }
}

Step Scheduler::schedule() {
  Step step;
  if (blocked == nullptr) {
    const auto [type, process] = addProcess();
    step.type = type;
    step.process = process;
  } else if (memoryManager->allocate(*blocked)) {
    step.type = StepType::UNLOCKED;
    step.process = *blocked;
    processes.push(*blocked);
    blocked.reset();
  } else {
    step.type = StepType::BLOCKED;
    step.process = *blocked;
  }
  Process curr = processes.front();
  step.current = curr;
  // ejecuta el proceso actual (le resta los quantum)
  curr.execute(systemQuantum);
  // elimina el proceso de la cola
  processes.pop();
  // si el proceso sigue vivo lo agrega al final de la cola y lo actualiza en
  // la memoria
  if (curr.isAlive()) {
    processes.push(curr);
    memoryManager->reallocate(curr);
  } else {
    // al terminar el proceso, lo elimina de la memoria
    memoryManager->deallocate(curr);
  }
  step.queue = normalize();
  step.memory = memoryManager->normalize();

  return step;
}

void Scheduler::clear() {
  memoryManager->clear();
  while (!processes.empty()) processes.pop();
}

std::list<Process> Scheduler::normalize() const {
  std::queue<Process> qu = processes;
  std::list<Process> proc;

  while (!qu.empty()) {
    proc.push_back(qu.front());
    qu.pop();
  }

  return proc;
}

std::ostream& operator<<(std::ostream& os, const Scheduler& obj) {
  for (const auto process : obj.normalize()) {
    os << process << " ";
  }

  return os;
}
