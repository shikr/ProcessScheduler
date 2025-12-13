#include "Timer.h"

#include <chrono>
#include <functional>
#include <thread>

Timer::Timer(std::function<void()> f, std::chrono::milliseconds* d) : fn(f), delay(d) {}

void Timer::start() {
  // solo pueden estar abiertos dos hilos, el que está en ejecución y el que espera a que
  // termine el anterior
  if (waiting == 0) {
    running = true;
    std::thread([&] {
      do {
        waiting++;
        auto end = std::chrono::system_clock::now() + *delay;
        // usar sleep_for generaría tiempos puertos
        while (std::chrono::system_clock::now() < end && running);
        if (running) fn();
        waiting--;
      } while (running);
    }).detach();
  } else if (waiting == 1) {
    // espera a que termine de ejecutarse el hilo principal para iniciar uno nuevo
    std::thread([&] {
      // al sumar 2 previene que entre en este condicional cuando el hilo principal
      // termine pero este no
      waiting += 2;
      while (waiting > 1);
      waiting -= 2;
      start();
    }).detach();
  }
}

void Timer::stop() { running = false; }

bool Timer::isRunning() { return running; }
