#include "MemoryBar.h"

#include <cmath>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

static Color processColor(int pid) {
  if (pid <= 0) return Color::White;

  const float kGoldenRatio = 0.6180339887f;
  float hue = std::fmod(pid * kGoldenRatio, 1.0f);

  return Color::HSV(hue * 255, 204, 178);
}

Component MemoryBar(std::function<ftxui::Element(ftxui::Elements)> body,
                    std::unique_ptr<Step>* step, int* memorySize) {
  return Renderer([=] {
    Elements blocks;
    std::list<MemoryBlock> memory;

    int chunkSize = 3;

    if (*step)
      memory = step->get()->memory;
    else
      memory.push_back(
          {.start = 0, .size = *memorySize, .isFree = true, .process = nullptr});
    auto value = 200 / (double)*memorySize;

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

    return body(blocks);
  });
}
