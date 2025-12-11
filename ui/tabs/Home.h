#ifndef PROCESSSCHEDULER_HOME_H
#define PROCESSSCHEDULER_HOME_H
#include <ftxui/component/component_base.hpp>
#include <functional>
#include <memory>

#include "../../memory/BaseMemory.h"

struct SchedulerParams {
  std::unique_ptr<BaseMemory>* memory;
  int *memorySize, *processMemory, *processQuantum, *systemQuantum;
};

ftxui::Component Home(SchedulerParams, std::function<void()> start,
                      std::function<void()> exit);

#endif
