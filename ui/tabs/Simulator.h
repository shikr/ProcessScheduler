#ifndef PROCESSSCHEDULER_SIMULATOR_H
#define PROCESSSCHEDULER_SIMULATOR_H
#include <ftxui/component/component_base.hpp>
#include <functional>
#include <memory>

#include "../../base/Scheduler.h"

struct SimulatorParams {
  std::unique_ptr<Step>* step;
  std::unique_ptr<Scheduler>* scheduler;
  int* memorySize;
  int* systemQuantum;
  int* processMemory;
  int* processQuantum;
};

ftxui::Component Simulator(SimulatorParams, std::function<void()>);
#endif  // !PROCESSSCHEDULER_SIMULATOR_H
