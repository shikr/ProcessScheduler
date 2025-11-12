//
// Created by crist on 11/11/2025.
//

#ifndef PROCESSSCHEDULER_FIRSTMEMORY_H
#define PROCESSSCHEDULER_FIRSTMEMORY_H
#include "BaseMemory.h"

class FirstMemory final : public BaseMemory {
public:
    bool allocate(const Process &process) override;
    void deallocate(const Process &process) override;
};


#endif //PROCESSSCHEDULER_FIRSTMEMORY_H