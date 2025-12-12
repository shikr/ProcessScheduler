//
// Created by crist on 11/10/2025.
//

#ifndef PROCESSSCHEDULER_PROCESS_H
#define PROCESSSCHEDULER_PROCESS_H
#include <ostream>

class Process {
  static int currentProcess;
  int quantum;
  int memory;
  int pid;

 public:
  Process();
  Process(int maxMemory, int maxQuantum);
  void execute(int);
  [[nodiscard]] int getMemory() const { return memory; }
  [[nodiscard]] int getPid() const { return pid; }
  [[nodiscard]] int getQuantum() const { return quantum; }
  [[nodiscard]] bool isAlive() const;

  static void Reset() { currentProcess = 1; }

  friend std::ostream& operator<<(std::ostream&, const Process&);
};

#endif  // PROCESSSCHEDULER_PROCESS_H
