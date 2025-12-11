#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>

#include "base/Scheduler.h"
#include "memory/FirstMemory.h"
#include "ui/tabs/Home.h"

int main() {
  int memorySize = 1024;
  int processMemory = 128;
  int processQuantum = 10;
  int systemQuantum = 4;
  int tabSelector = 0;
  std::unique_ptr<Scheduler> scheduler;
  std::unique_ptr<BaseMemory> memory = std::make_unique<FirstMemory>(memorySize);
  ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FullscreenAlternateScreen();

  // clang-format off
  auto component = ftxui::Container::Tab({
    Home({
      .memory = &memory,
      .memorySize = &memorySize,
      .processMemory = &processMemory,
      .processQuantum = &processQuantum,
      .systemQuantum = &systemQuantum
    },
         [] {}, screen.ExitLoopClosure()
  )}, &tabSelector);
  // clang-format on

  screen.Loop(component);
}
