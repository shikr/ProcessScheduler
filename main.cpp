#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

#include "base/Scheduler.h"
#include "memory/FirstMemory.h"
#include "ui/tabs/Home.h"
#include "ui/tabs/Simulator.h"

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
        tabSelector = 1;
      },
      screen.ExitLoopClosure()),
      Simulator({
        .step = &step,
        .scheduler = &scheduler,
        .memorySize = &memorySize,
        .systemQuantum = &systemQuantum,
        .processMemory = &processMemory,
        .processQuantum = &processQuantum
      },
      [&] {
        tabSelector = 0;
      }),
    },
    &tabSelector
  );
  // clang-format on

  screen.Loop(component);
}
