//
// Created by crist on 11/11/2025.
//

#ifndef PROCESSSCHEDULER_WORSTMEMORY_H
#define PROCESSSCHEDULER_WORSTMEMORY_H
#include "BaseMemory.h"


class WorstMemory final : public BaseMemory {
public:
    bool allocate(const Process &process) override;
};


#endif //PROCESSSCHEDULER_WORSTMEMORY_H