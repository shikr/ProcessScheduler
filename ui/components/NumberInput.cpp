#include "NumberInput.h"

#include <cctype>
#include <charconv>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/util/ref.hpp>
#include <string>

using namespace ftxui;

Component NumberInput(NumberInputOption option) {
  class Impl : public ComponentBase {
    std::string input;
    ftxui::Ref<int> value;

   public:
    Impl(NumberInputOption opt) : value(opt.value), input(std::to_string(*opt.value)) {
      auto component = Input({
                           .content = &input,
                           .placeholder = opt.placeholder,
                           .transform = opt.transform,
                           .password = opt.password,
                           .multiline = false,
                           .insert = opt.insert,
                           .on_change =
                               [&, opt] {
                                 int previous = *value;
                                 if (input.empty()) {
                                   *value = std::max(*opt.min, 0);
                                 } else {
                                   auto begin = input.data();
                                   auto end = begin + input.size();
                                   auto result = std::from_chars(begin, end, *value);

                                   if (result.ec != std::errc{} || result.ptr != end ||
                                       *value < *opt.min || *value > *opt.max) {
                                     *value = previous;
                                     input = std::to_string(*value);
                                     return;
                                   }
                                 }

                                 if (opt.on_change) opt.on_change();
                               },
                           .on_enter = opt.on_enter,
                           .cursor_position = opt.cursor_position,
                       }) |
                       CatchEvent([&](Event ev) {
                         return ev.is_character() && !std::isdigit(ev.character()[0]);
                       });

      Add(component);
    }
  };

  return Make<Impl>(option);
}
