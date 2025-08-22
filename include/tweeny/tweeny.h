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
#include <type_traits>

#include "detail/tuple-utilities.h"

namespace tweeny {
  /**
   * @brief Primary template for the tween builder type.
   *
   * Models a fluent builder used to construct tween instances for one or more parts.
   * The boolean template parameter encodes the builder state: when false, no to() call
   * has been made yet; when true, easing functions and durations can be configured.
   *
   * @tparam WasToCalled Compile-time flag indicating whether at least one to() call has been made.
   * @tparam FirstValue Type of the first tweened component.
   * @tparam RemainingValues Types of the remaining tweened components.
   */
  template <bool WasToCalled, typename FirstValue, typename... RemainingValues>
  class tweeny_builder;

  template <typename FirstValue, typename... RemainingValues>
  /**
   * @brief Builder specialization for the stage before the first to() call.
   *
   * Holds the initial key-frame values and allows adding the next key-frame via to().
   * Calling `to()` transitions the builder to the WasToCalled=true specialization; build()
   * can be used to create a tween with the currently collected key-frames.
   *
   * @tparam FirstValue Type of the first tweened component.
   * @tparam RemainingValues Types of the remaining tweened components.
   */
  class tweeny_builder<false, FirstValue, RemainingValues...> {
    typedef std::vector<detail::key_frame<FirstValue, RemainingValues...>> key_frames_t;
    typedef tween<FirstValue, RemainingValues...> tween_t;
    static size_t constexpr value_count = 1 + sizeof...(RemainingValues);

    public:
      explicit tweeny_builder(FirstValue firstValue, RemainingValues... remainingValues) {
        key_frames.emplace_back(firstValue, remainingValues...);
      }

      explicit tweeny_builder(key_frames_t && frames) : key_frames(std::move(frames)) {}
      explicit tweeny_builder(const key_frames_t & frames) : key_frames(frames) {}

      tweeny_builder<true, FirstValue, RemainingValues...> to(const FirstValue & firstValue, const RemainingValues &... remainingValues) & {
        key_frames.emplace_back(firstValue, remainingValues...);
        return tweeny_builder<true, FirstValue, RemainingValues...>(key_frames);
      }

      tweeny_builder<true, FirstValue, RemainingValues...> to(const FirstValue & firstValue, const RemainingValues &... remainingValues) && {
        key_frames.emplace_back(firstValue, remainingValues...);
        return tweeny_builder<true, FirstValue, RemainingValues...>(std::move(key_frames));
      }

    private:
      key_frames_t key_frames;
  };

  template <typename FirstValue, typename... RemainingValues>
  /**
   * @brief Builder specialization for the stage after at least one to() call.
   *
   * In this stage, additional key-frames can be appended with to(), easing functions can be
   * specified using via(), and per-component or uniform frame counts can be set with during().
   * Finally, build() materializes the configured tween.
   *
   * @tparam FirstValue Type of the first tweened component.
   * @tparam RemainingValues Types of the remaining tweened components.
   */
  class tweeny_builder<true, FirstValue, RemainingValues...> {
    typedef std::vector<detail::key_frame<FirstValue, RemainingValues...>> key_frames_t;
    typedef tween<FirstValue, RemainingValues...> tween_t;
    static size_t constexpr value_count = 1 + sizeof...(RemainingValues);

    public:
      explicit tweeny_builder(FirstValue firstValue, RemainingValues... remainingValues) {
        key_frames.emplace_back(firstValue, remainingValues...);
      }

      explicit tweeny_builder(key_frames_t && frames) : key_frames(std::move(frames)) {}
      explicit tweeny_builder(const key_frames_t & frames) : key_frames(frames) {}

      tweeny_builder to(const FirstValue & firstValue, const RemainingValues &... remainingValues) & {
        key_frames.emplace_back(firstValue, remainingValues...);
        return tweeny_builder(key_frames);
      }

      tweeny_builder to(const FirstValue & firstValue, const RemainingValues &... remainingValues) && {
        key_frames.emplace_back(firstValue, remainingValues...);
        return tweeny_builder(std::move(key_frames));
      }

      template<typename... EasingFunctionTypes>
      tweeny_builder & via(EasingFunctionTypes... easing_functions) {
        static_assert(sizeof...(EasingFunctionTypes) == value_count,
                      "via() must have one easing function per tween component");
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

      tweeny_builder & during(uint32_t frame_count) {
        auto & key_frame = key_frames.at(key_frames.size() - 2);
        std::fill(
          std::begin(key_frame.tween_frame_counts),
          std::end(key_frame.tween_frame_counts),
          frame_count
        );
        fix_frame_positions();
        return *this;
      }

      tween_t build() const & { return tween(key_frames); }
      tween_t build() && { return tween(std::move(key_frames)); }

    private:
      key_frames_t key_frames;
      void fix_frame_positions() {
        uint32_t key_frame_position = 0;
        for (auto & key_frame : key_frames) {
          key_frame.position = key_frame_position;
          key_frame_position += key_frame.highest_frame_count();
        }
      }
  };

  template <typename FirstValue, typename... RemainingValues>
  tweeny_builder<false, FirstValue, RemainingValues...> from(FirstValue first_value, RemainingValues... remaining_values) {
    return tweeny_builder<false, FirstValue, RemainingValues...>(first_value, remaining_values...);
  }
}

#endif //TWEENY_TWEENY_H
