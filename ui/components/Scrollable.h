#ifndef PROCESSSCHDULER_SCROLLABLE_H
#define PROCESSSCHDULER_SCROLLABLE_H
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/util/ref.hpp>
#include <functional>

struct ScrollableParams {
  ftxui::Ref<float> scroll_x = 0.0;
  ftxui::Ref<float> scroll_y = 0.0;
  ftxui::Ref<float> increment = 0.1;
};

ftxui::Component Scrollable(std::function<ftxui::Element(bool focused)>,
                            ScrollableParams);
ftxui::Component Scrollable(std::function<ftxui::Element(bool focused)>);

#endif  // !PROCESSSCHDULER_SCROLLABLE_H
