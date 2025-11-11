//
// Created by crist on 11/10/2025.
//

#include "random.h"
#include <random>

static std::random_device rd;
static std::mt19937 eng(rd());

int random(const int min, const int max) {
    std::uniform_int_distribution distribution(min, max);

    return distribution(eng);
}

int random(std::uniform_int_distribution<> distribution) {
    return distribution(eng);
}