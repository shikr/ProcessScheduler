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
    Process(int maxMemory, int maxQuantum);
    void execute();
    [[nodiscard]] int getMemory() const { return memory; }
    [[nodiscard]] int getPid() const { return pid; }
    [[nodiscard]] bool isAlive() const;

    friend std::ostream& operator<<(std::ostream&, const Process&);
};


#endif //PROCESSSCHEDULER_PROCESS_H
