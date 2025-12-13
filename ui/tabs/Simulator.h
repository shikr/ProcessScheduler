#ifndef PROCESSSCHEDULER_SIMULATOR_H
#define PROCESSSCHEDULER_SIMULATOR_H
#include <chrono>
#include <ftxui/component/component_base.hpp>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../../base/Scheduler.h"

struct SimulatorParams {
  std::unique_ptr<Step>* step;
  std::vector<std::string>* log;
  int* memorySize;
  int* systemQuantum;
  int* processMemory;
  int* processQuantum;
  std::vector<int>* memoryHistory;
  std::chrono::milliseconds* delay;
  std::function<void()> schedule;
};

ftxui::Component Simulator(SimulatorParams, std::function<bool()> playpause,
                           std::function<void()> back);
#endif  // !PROCESSSCHEDULER_SIMULATOR_H
