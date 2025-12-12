#include "Simulator.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "../../base/Scheduler.h"
#include "../components/MemoryBar.h"
#include "../components/Scrollable.h"

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

Component Simulator(SimulatorParams params, std::function<void()> back) {
  static std::vector<std::string> log;
  static int view = 0;
  static float scroll_y = 1.f;

  auto button = Button("Siguiente", [=] {
    auto step = params.scheduler->get()->schedule();
    *params.step = std::make_unique<Step>(step);
    std::ostringstream ss;

    ss << step;

    log.push_back(ss.str());
    scroll_y = 1.f;
  });

  auto stop_button = Button("Inicio", [=] {
    log.clear();
    params.scheduler->get()->clear();
    scroll_y = 1.f;
    view = 0;
    back();
  });

  std::vector<std::string> entries = {"Ciclo", "Registros"};

  auto view_menu = Menu(entries, &view, {.on_enter = [=] { button->TakeFocus(); }});

  auto status = Container::Tab(
      {MemoryBar([](Elements blocks) { return hflow(blocks); }, params.step,
                 params.memorySize),
       Scrollable(
           [](bool focused) {
             return vbox(logs(log)) | hscroll_indicator | vscroll_indicator |
                    color(focused ? Color::Yellow : Color::White);
           },
           {.scroll_y = &scroll_y})},
      &view);

  auto controls = Container::Horizontal({view_menu, button, stop_button});
  auto container = Container::Vertical({status, controls});

  return Renderer(container, [=] {
    return vbox({window(text(entries[view]), status->Render()) | flex,
                 window(text("Controles"),
                        hbox({vbox({text("Vista"), view_menu->Render()}), filler(),
                              button->Render(), stop_button->Render(), filler()}))});
  });
}
