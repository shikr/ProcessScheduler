#include <chrono>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>
#include <string>
#include <vector>

#include "base/Process.h"
#include "base/Scheduler.h"
#include "memory/FirstMemory.h"
#include "ui/tabs/Home.h"
#include "ui/tabs/Simulator.h"
#include "util/Timer.h"

int main() {
  int memorySize = 1024;
  int processMemory = 128;
  int processQuantum = 10;
  int systemQuantum = 4;
  int tabSelector = 0;
  std::unique_ptr<Scheduler> scheduler;
  std::shared_ptr<BaseMemory> memory = std::make_shared<FirstMemory>(memorySize);
  ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FullscreenAlternateScreen();
  std::unique_ptr<Step> step = nullptr;
  auto delay = std::chrono::milliseconds(1000);
  std::vector<std::string> logs;

  auto schedule = [&] {
    if (step)
      *step = scheduler->schedule();
    else
      step = std::make_unique<Step>(scheduler->schedule());

    std::ostringstream ss;
    ss << *step;

    logs.push_back(ss.str());
  };

  Timer timer(
      [&] {
        schedule();
        screen.RequestAnimationFrame();
      },
      &delay);

  // clang-format off
  auto component = ftxui::Container::Tab(
    {
      Home({
        .memory = &memory,
        .memorySize = &memorySize,
        .processMemory = &processMemory,
        .processQuantum = &processQuantum,
        .systemQuantum = &systemQuantum
      },
      [&] {
        scheduler = std::make_unique<Scheduler>(processMemory, processQuantum, memory, systemQuantum);
        timer.start();
        tabSelector = 1;
      },
      screen.ExitLoopClosure()),
      Simulator({
        .step = &step,
        .log = &logs,
        .memorySize = &memorySize,
        .systemQuantum = &systemQuantum,
        .processMemory = &processMemory,
        .processQuantum = &processQuantum,
        .schedule = schedule,
      },
      [&] {
        if (timer.isRunning()) timer.stop();
        else timer.start();

        return timer.isRunning();
      },
      [&] {
        timer.stop();
        logs.clear();
        Process::Reset();
        scheduler->clear();
        step.reset();
        tabSelector = 0;
      }),
    },
    &tabSelector
  );
  // clang-format on

  screen.Loop(component);
}
