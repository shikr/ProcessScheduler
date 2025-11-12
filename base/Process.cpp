//
// Created by crist on 11/10/2025.
//

#include "Process.h"
#include "../util/random.h"
#include <iostream>
#include <ostream>

int Process::currentProcess = 1;

Process::Process(const int maxMemory, const int maxQuantum) {
    pid = currentProcess++;
    memory = random(1, maxMemory);
    quantum = random(1, maxQuantum);
}

void Process::execute() {
    quantum--;
}

bool Process::isAlive() const {
    return quantum > 0;
}

std::ostream& operator<<(std::ostream& os, const Process& process) {
    os << "[" << process.pid << ", " << process.memory << ", " << process.quantum << "]";
    return os;
}
