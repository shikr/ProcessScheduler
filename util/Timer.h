#ifndef PROCESSSCHEDULER_TIMER_H
#define PROCESSSCHEDULER_TIMER_H
#include <chrono>
#include <functional>

class Timer {
  bool running = false;
  int waiting = false;
  std::chrono::milliseconds* delay;
  std::function<void()> fn;

 public:
  Timer(std::function<void()>, std::chrono::milliseconds*);

  void start();
  void stop();
  bool isRunning();
};

#endif  // !PROCESSSCHEDULER_TIMER_H
