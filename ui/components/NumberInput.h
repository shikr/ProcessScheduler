#ifndef PROCESSSCHEDULER_NUMBERINPUT_H
#define PROCESSSCHEDULER_NUMBERINPUT_H
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/util/ref.hpp>
#include <functional>
#include <limits>

struct NumberInputOption {
  ftxui::Ref<int> value;
  ftxui::Ref<int> min = std::numeric_limits<int>::min();
  ftxui::Ref<int> max = std::numeric_limits<int>::max();
  ftxui::StringRef placeholder;
  std::function<ftxui::Element(ftxui::InputState)> transform;
  ftxui::Ref<bool> password;
  ftxui::Ref<bool> insert;
  std::function<void()> on_change;
  std::function<void()> on_enter;
  ftxui::Ref<int> cursor_position;
};

ftxui::Component NumberInput(NumberInputOption);

#endif  // !PROCESSSCHEDULER_NUMBERINPUT_H
