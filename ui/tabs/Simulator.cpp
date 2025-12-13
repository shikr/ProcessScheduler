#include "Simulator.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "../../base/Scheduler.h"
#include "../../util/color.h"
#include "../components/Scrollable.h"
#include "../elements/memoryBar.h"
#include "../elements/processQueue.h"

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

Component Simulator(SimulatorParams params, std::function<bool()> playpause,
                    std::function<void()> back) {
  static int view = 0;
  static float scroll_y = 1.f;
  static std::string controlLabel = "Pausar";

  auto playpause_button = Button(&controlLabel, [=] {
    if (playpause())
      controlLabel = "Pausar";
    else
      controlLabel = "Reanudar";
  });

  auto next_button = Button("Siguiente", [=] {
    params.schedule();
    scroll_y = 1.f;
  });

  auto stop_button = Button("Inicio", [=] {
    scroll_y = 1.f;
    view = 0;
    controlLabel = "Pausar";
    back();
  });

  std::vector<std::string> entries = {"Estado", "Registros"};
  auto view_menu = Menu(entries, &view, {.on_enter = [=] { next_button->TakeFocus(); }});

  auto controls =
      Container::Horizontal({view_menu, playpause_button, next_button, stop_button});

  auto status_component = Renderer([=] {
    Elements info = {
        text("Tamaño de la memoria: " + std::to_string(*params.memorySize)),
        text("Cuanto del sistema: " + std::to_string(*params.systemQuantum)),
        text("Tamaño máximo de memoria por proceso: " +
             std::to_string(*params.processMemory)),
        text("Cuanto máximo por proceso: " + std::to_string(*params.processQuantum))};
    if (*params.step) {
      std::ostringstream ss;
      std::string type;
      switch (params.step->get()->type) {
        case StepType::NEW:
          type = "Nuevo";
          break;
        case StepType::BLOCKED:
          type = "Bloqueado";
          break;
        default:
          type = "Desbloqueado";
          break;
      }
      ss << params.step->get()->process;
      info.push_back(hbox(
          {text(type + ": "),
           text(ss.str()) | color(processColor(params.step->get()->process.getPid()))}));
    }
    return vbox({window(text("Memoria"), memoryBar(params.step, params.memorySize)),
                 window(text("Información"), vbox(info)),
                 window(text("Cola"), processQueue(params.step))});
  });

  auto status = Container::Tab(
      {status_component, Scrollable(
                             [=](bool focused) {
                               return vbox(logs(*params.log)) | hscroll_indicator |
                                      vscroll_indicator |
                                      color(focused ? Color::Yellow : Color::White);
                             },
                             {.scroll_y = &scroll_y})},
      &view);

  auto container = Container::Vertical({status, controls});

  return Renderer(container, [=] {
    return vbox({window(text(entries[view]), status->Render()) | flex,
                 window(text("Controles"),
                        hbox({vbox({text("Vista"), view_menu->Render()}), filler(),
                              playpause_button->Render(), next_button->Render(),
                              stop_button->Render(), filler()}))});
  });
}
