#include "Scrollable.h"

#include <algorithm>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/util/ref.hpp>
#include <functional>

using namespace ftxui;

class Impl : public ComponentBase {
  Ref<float> scroll_x;
  Ref<float> scroll_y;
  Ref<float> increment;

 public:
  Impl(Ref<float> x, Ref<float> y, Ref<float> inc, std::function<Element(bool)> body)
      : scroll_x(x), scroll_y(y), increment(inc) {
    auto event = CatchEvent([&](Event ev) {
      if (ev == Event::ArrowUp && *scroll_y > 0.f) {
        *scroll_y = std::max(0.f, *scroll_y - *increment);
        return true;
      } else if (ev == Event::ArrowDown && *scroll_y < 1.f) {
        *scroll_y = std::min(1.f, *scroll_y + *increment);
        return true;
      } else if (ev == Event::ArrowLeft && *scroll_x > 0.f) {
        *scroll_x = std::max(0.f, *scroll_x - *increment);
        return true;
      } else if (ev == Event::ArrowRight && *scroll_x < 1.f) {
        *scroll_x = std::min(1.f, *scroll_x + *increment);
        return true;
      } else if (ev == Event::PageUp) {
        *scroll_y = 0.f;
        return true;
      } else if (ev == Event::PageDown) {
        *scroll_y = 1.f;
        return true;
      } else if (ev.is_mouse() && ev.mouse().button == Mouse::WheelUp &&
                 *scroll_y > 0.f) {
        *scroll_y = std::max(0.f, *scroll_y - *increment);
        return true;
      } else if (ev.is_mouse() && ev.mouse().button == Mouse::WheelDown &&
                 *scroll_y < 1.f) {
        *scroll_y = std::min(1.f, *scroll_y + *increment);
        return true;
      }

      return false;
    });

    Add(Renderer([&, body](bool focused) {
          return body(focused) | focusPositionRelative(*scroll_x, *scroll_y) | frame;
        }) |
        event);
  }
};

Component Scrollable(std::function<Element(bool)> body, ScrollableParams params) {
  return Make<Impl>(params.scroll_x, params.scroll_y, params.increment, body);
}

Component Scrollable(std::function<Element(bool)> body) {
  return Make<Impl>(0, 0, 0.1, body);
}
