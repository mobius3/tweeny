/*
This file is part of the Tweeny library.

Copyright (c) 2016-2025 Leonardo Guilherme Lucena de Freitas
Copyright (c) 2016 Guilherme R. Costa

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
#
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef TWEENY_TWEENY_H
#define TWEENY_TWEENY_H

#include "tween.h"
#include <tuple>

#include "detail/tuple-utilities.h"

namespace tweeny {
  template <typename FirstValue, typename... RemainingValues>
  class tweeny_builder {
    typedef std::vector<detail::key_frame<FirstValue, RemainingValues...>> key_frames_t;
    typedef tween<FirstValue, RemainingValues...> tween_t;
    static size_t constexpr value_count = 1 + sizeof...(RemainingValues);

    public:
      explicit tweeny_builder(FirstValue firstValue, RemainingValues... remainingValues) {
        key_frames.emplace_back(firstValue, remainingValues...);
      }

      tweeny_builder & to(const FirstValue & firstValue, const RemainingValues &... remainingValues) {
        key_frames.emplace_back(firstValue, remainingValues...);
        return *this;
      }

      template<typename... EasingFunctionTypes> tweeny_builder & via(EasingFunctionTypes... easing_functions) {
        static_assert(sizeof...(EasingFunctionTypes) == value_count,
                      "via() must have one easing function per tween component");

        /* HOLD.
         * the intention here is to access the “previous” key frame
         * after you’ve just pushed a new one with to(...), via(...) configures the easing
         * for the segment that starts at the previous frame.
         */
        auto & key_frame = key_frames.at(key_frames.size() - 2);
        key_frame.easing_functions = std::make_tuple(easing_functions...);
        return *this;
      }

      template<typename EasingFunctionType>
      tweeny_builder & via(EasingFunctionType easing_function) {
        auto & key_frame = key_frames.at(key_frames.size() - 2);
        key_frame.easing_functions = detail::make_repeated_tuple<EasingFunctionType, value_count>(easing_function);
        return *this;
      }

      template<typename... FrameCountsType>
      tweeny_builder & during(FrameCountsType... frame_counts) {
        static_assert(sizeof...(FrameCountsType) == value_count,
                     "during() must have one frame count per tween component");

        static_assert((std::is_same_v<std::decay_t<FrameCountsType>, uint32_t> && ...),
                      "during() parameters must be of type uint32_t");

        auto & key_frame = key_frames.at(key_frames.size() - 2);
        std::array<uint32_t, sizeof...(FrameCountsType)> frame_counts_array = { frame_counts... };
        std::copy(
          std::begin(frame_counts_array),
          std::end(frame_counts_array),
          std::begin(key_frame.tween_frame_counts));

        fix_frame_positions();
        return *this;
      }

      tweeny_builder & during(uint16_t frame_count) {
        auto & key_frame = key_frames.at(key_frames.size() - 2);
        std::fill(
          std::begin(key_frame.tween_frame_counts),
          std::end(key_frame.tween_frame_counts),
          frame_count
        );

        fix_frame_positions();
        return *this;
      }

      tween_t build() const & {
        return tween(key_frames);
      }

      tween_t build() && {
        return tween(std::move(key_frames));
      }

    private:
      key_frames_t key_frames;
      void fix_frame_positions() {
        uint16_t key_frame_position = 0;
        for (auto & key_frame : key_frames) {
          key_frame.position = key_frame_position;
          key_frame_position += key_frame.highest_frame_count();
        }
      }
  };

  template <typename FirstValue, typename... RemainingValues>
  tweeny_builder<FirstValue, RemainingValues...> from(FirstValue first_value, RemainingValues... remaining_values) {
    return tweeny_builder<FirstValue, RemainingValues...>(first_value, remaining_values...);
  }
}

#include "easing/easing.h"

#endif //TWEENY_TWEENY_H
