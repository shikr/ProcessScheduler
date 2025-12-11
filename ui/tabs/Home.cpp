#include "Home.h"

#include <cmath>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <functional>
#include <string>
#include <vector>

#include "../../memory/BestMemory.h"
#include "../../memory/FirstMemory.h"
#include "../../memory/WorstMemory.h"
#include "../components/NumberInput.h"

using namespace ftxui;

static std::vector<std::string> fit_entries = {"Primer Ajuste", "Mejor Ajuste",
                                               "Peor Ajuste"};
static std::vector<std::string> memory_entries = {"1 MB", "4 MB", "8 MB"};

static int size(int memory) {
  if (memory == 0) return 1;
  if (memory == 1) return 4;

  return 2 * size(memory - 1);
}

static std::unique_ptr<BaseMemory> memoryFit(int fit, int memory) {
  switch (fit) {
    case 0:
      return std::make_unique<FirstMemory>(memory);
    case 1:
      return std::make_unique<BestMemory>(memory);
    default:
      return std::make_unique<WorstMemory>(memory);
  }
}

static ComponentDecorator CatchSlider(int* max, int* value) {
  return CatchEvent([=](Event ev) {
    if (ev.is_character() && ev.character()[0] >= '0' && ev.character()[0] <= '9') {
      *value = ceil((double)(*max) / 10) * (ev.character()[0] - '0') + 1;

      return true;
    } else if (ev == Event::ArrowLeftCtrl) {
      *value -= ceil((double)(*max) / 10);
      if (*value < 1) *value = 1;

      return true;
    } else if (ev == Event::ArrowRightCtrl) {
      *value += ceil((double)(*max) / 10);
      if (*value > *max) *value = *max;

      return true;
    }
    return false;
  });
}

Component Home(SchedulerParams params, std::function<void()> start,
               std::function<void()> exit) {
  static int fit = 0;
  static int memory = 0;
  static int maxMemory = *params.memorySize / 2;

  auto quantum_slider = Slider<int>({.value = params.systemQuantum,
                                     .min = 1,
                                     .max = params.processQuantum,
                                     .increment = 1}) |
                        CatchSlider(params.processQuantum, params.systemQuantum);
  auto quantum_input =
      NumberInput({.value = params.processQuantum,
                   .min = 1,
                   .placeholder = "Cuanto por proceso",
                   .on_change =
                       [=] {
                         if (*params.systemQuantum > *params.processQuantum)
                           *params.systemQuantum = *params.processQuantum;
                       },
                   .on_enter = [=] { quantum_slider->TakeFocus(); }});

  auto quantum_container = Container::Horizontal({quantum_input, quantum_slider});

  auto memory_slider = Slider<int>({
                           .value = params.processMemory,
                           .min = 1,
                           .max = &maxMemory,
                           .increment = 1,
                       }) |
                       CatchSlider(&maxMemory, params.processMemory);
  auto memory_menu = Menu(&memory_entries, &memory,
                          {.on_change =
                               [=] {
                                 *params.memorySize = size(memory) * 1024;
                                 *params.memory = memoryFit(fit, *params.memorySize);
                                 maxMemory = *params.memorySize / 2;
                                 if (*params.processMemory > maxMemory)
                                   *params.processMemory = maxMemory;
                               },
                           .on_enter = [=] { memory_slider->TakeFocus(); }});

  auto memory_container = Container::Horizontal({memory_menu, memory_slider});

  auto fit_menu =
      Menu(&fit_entries, &fit,
           {.on_change = [=] { *params.memory = memoryFit(fit, *params.memorySize); },
            .on_enter = [=] { memory_menu->TakeFocus(); }});

  auto form = Container::Vertical({fit_menu, memory_container, quantum_container});

  auto start_button =
      Button("Iniciar", start, ButtonOption::Animated(Color::Green)) | borderEmpty;
  auto exit_button =
      Button(" Salir ", exit, ButtonOption::Animated(Color::Red)) | borderEmpty;

  auto button_container = Container::Horizontal({start_button, exit_button});

  return Renderer(Container::Vertical({form, button_container}), [=] {
    return hbox(
        {filler(),
         vbox(
             filler(),
             window(
                 text("Parámetros:"),
                 vbox(
                     {vbox({text("Ajuste:"), fit_menu->Render()}), separator(),
                      hbox({vbox({text("Tamaño de la memoria:"), memory_menu->Render()}),
                            separator(),
                            vbox({text("Memoria por proceso:"), memory_slider->Render(),
                                  text(std::to_string(*params.processMemory) + " KB")})}),
                      separator(),
                      hbox({vbox({text("Cuanto maximo por proceso:"),
                                  quantum_input->Render()}),
                            separator(),
                            vbox({text("Cuanto del sistema:"),
                                  hbox({quantum_slider->Render(),
                                        text(std::to_string(
                                            *params.systemQuantum))})})})})),
             hbox({filler(), button_container->Render(), filler()}), filler()),
         filler()});
  });
}
