//
// Created by crist on 11/11/2025.
//

#ifndef PROCESSSCHEDULER_BESTMEMORY_H
#define PROCESSSCHEDULER_BESTMEMORY_H
#include "BaseMemory.h"


class BestMemory final : public BaseMemory {
public:
    bool allocate(const Process &process) override;
};


#endif //PROCESSSCHEDULER_BESTMEMORY_H