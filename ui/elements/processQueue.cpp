#include "processQueue.h"

#include <ftxui/dom/elements.hpp>
#include <memory>
#include <string>

#include "../../base/Scheduler.h"

using namespace ftxui;

Element processQueue(std::unique_ptr<Step>* step) {
  Elements blocks;

  if (*step) {
    auto qu = step->get()->queue;

    for (const auto& process : qu) {
      blocks.push_back(
          window(text("P" + std::to_string(process.getPid())),
                 vbox({text("Tamaño: " + std::to_string(process.getMemory()) + " KB"),
                       text("Cuantos: " + std::to_string(process.getQuantum()))})));
    }
  }

  Elements emptyElement = {text("No hay procesos en la cola.")};

  return hflow(blocks.empty() ? emptyElement : blocks);
}
