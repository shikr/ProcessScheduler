//
// Created by crist on 11/10/2025.
//

#ifndef PROCESSSCHEDULER_RANDOM_H
#define PROCESSSCHEDULER_RANDOM_H
#include <random>

int random(int min, int max);
int random(std::uniform_int_distribution<> distribution);

#endif  // PROCESSSCHEDULER_RANDOM_H
