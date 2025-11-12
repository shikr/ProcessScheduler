#include "base/Scheduler.h"
#include "memory/FirstMemory.h"

constexpr int MAX_MEMORY = 2048;
constexpr int MAX_QUANTUM = 5;

int main() {
    Scheduler scheduler(MAX_MEMORY, MAX_QUANTUM, new FirstMemory());
    scheduler.schedule();
}