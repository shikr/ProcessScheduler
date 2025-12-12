#include "Simulator.h"

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

Component Simulator(SimulatorParams params, std::function<void()> back) {
  static std::vector<std::string> log;

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

  auto container = Container::Horizontal({button, stop_button});

  return Renderer(container, [=] {
    return vbox(
        {window(text("Registros"), vbox(logs(log)) | focusPositionRelative(0.f, 1.f) |
                                       hscroll_indicator | vscroll_indicator | frame) |
             yflex,
         window(text("Controles"),
                hbox({filler(), button->Render(), stop_button->Render(), filler()}))});
  });
}
