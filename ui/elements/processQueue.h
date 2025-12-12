#ifndef PROCESSSCHEDULER_PROCESSQUEUE_H
#define PROCESSSCHEDULER_PROCESSQUEUE_H
#include <ftxui/dom/elements.hpp>
#include <memory>

#include "../../base/Scheduler.h"

ftxui::Element processQueue(std::unique_ptr<Step>*);

#endif  // !PROCESSSCHEDULER_PROCESSLIST_H
