//
// Created by crist on 11/10/2025.
//

#include "random.h"

#include <random>

static std::random_device rd;
static std::mt19937 eng(rd());

/**
 * Genera un numero aleatorio entre min y max
 */
int random(const int min, const int max) {
  // genera la distribucion entre los dos numeros
  std::uniform_int_distribution distribution(min, max);

  return distribution(eng);
}

/**
 * Genera un numero aleatorio a partir de una distribucion
 */
int random(std::uniform_int_distribution<> distribution) { return distribution(eng); }
