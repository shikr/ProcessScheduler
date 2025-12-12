#include "Simulator.h"

#include <cmath>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "../../base/Scheduler.h"

using namespace ftxui;

static std::vector<Element> logs(std::vector<std::string> log) {
  std::vector<Element> elements;
  bool first = true;

  for (const auto& reg : log) {
    if (!first) elements.push_back(separatorEmpty());
    first = false;

    elements.push_back(paragraph(reg));
  }

  return elements;
}

static Color processColor(int pid) {
  if (pid <= 0) return Color::White;

  const float kGoldenRatio = 0.6180339887f;
  float hue = std::fmod(pid * kGoldenRatio, 1.0f);

  return Color::HSV(hue * 255, 204, 178);
}

Component Simulator(SimulatorParams params, std::function<void()> back) {
  static std::vector<std::string> log;
  static int view = 0;

  auto button = Button("Siguiente", [=] {
    auto step = params.scheduler->get()->schedule();
    *params.step = std::make_unique<Step>(step);
    std::ostringstream ss;

    ss << step;

    log.push_back(ss.str());
  });

  auto stop_button = Button("Inicio", [=] {
    log.clear();
    params.scheduler->get()->clear();
    back();
  });

  auto view_menu = Menu(std::vector<std::string>{"Ciclo", "Registros"}, &view,
                        {.on_enter = [=] { button->TakeFocus(); }});

  auto container = Container::Horizontal({view_menu, button, stop_button});

  return Renderer(container, [=] {
    Elements blocks;
    std::list<MemoryBlock> memory;

    int chunkSize = 3;

    if (*params.step)
      memory = params.step->get()->memory;
    else
      memory.push_back(
          {.start = 0, .size = *params.memorySize, .isFree = true, .process = nullptr});
    auto value = 200 / (double)*params.memorySize;

    for (const auto& block : memory) {
      Color c = processColor(block.isFree ? 0 : block.process->getPid());
      std::string label =
          block.isFree ? " " : "P" + std::to_string(block.process->getPid());

      int numChunks = ceil(value * (double)block.size);
      int f = numChunks - label.size();

      if (f > 0)
        label = std::string(f / 2, ' ') + label + std::string(f / 2, ' ') +
                std::string(f % 2, ' ');

      for (int i = 0; i < label.size(); i += chunkSize)
        blocks.push_back(text(label.substr(i, chunkSize)) | bgcolor(c) |
                         color(Color::White));
    }

    return vbox({(view != 0 ? window(text("Registros"),
                                     vbox(logs(log)) | focusPositionRelative(0.f, 1.f) |
                                         hscroll_indicator | vscroll_indicator | frame)
                            : window(text("hola"), hflow(blocks))) |
                     flex,
                 window(text("Controles"),
                        hbox({vbox({text("Vista"), view_menu->Render()}), filler(),
                              button->Render(), stop_button->Render(), filler()}))});
  });
}
