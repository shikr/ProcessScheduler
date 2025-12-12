#include "color.h"

#include <cmath>
#include <ftxui/screen/color.hpp>

const float kGoldenRatio = 0.6180339887f;

ftxui::Color processColor(int pid) {
  if (pid <= 0) return ftxui::Color::White;

  float hue = std::fmod(pid * kGoldenRatio, 1.0f);

  return ftxui::Color::HSV(hue * 255, 204, 178);
}
