#ifndef PROCESSSCHEDULER_MEMORYBAR_H
#define PROCESSSCHEDULER_MEMORYBAR_H
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <functional>

#include "../../base/Scheduler.h"

ftxui::Component MemoryBar(std::function<ftxui::Element(ftxui::Elements)>,
                           std::unique_ptr<Step>*, int*);

#endif  // !PROCESSSCHEDULER_MEMORYBAR_H
