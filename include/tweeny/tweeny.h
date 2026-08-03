/*
This file is part of the Tweeny library.

Copyright (c) 2016-2026 Leonardo Guilherme Lucena de Freitas
Copyright (c) 2016 Guilherme R. Costa

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file tweeny.h
 * @brief Builder API for creating tweens.
 *
 * This file provides the fluent builder interface for constructing tween animations.
 * The typical workflow is: from() → to() → via() → during() → build()
 *
 * @code
 * auto tween = tweeny::from(0.0f).to(100.0f).via(easing::linear).during(60U).build();
 * @endcode
 */

#ifndef TWEENY_TWEENY_H
#define TWEENY_TWEENY_H

#include "tween.h"
#include <tuple>
#include <type_traits>

#include "detail/tuple-utilities.h"
#include "event.h"
#include "easing.h"

/**
 * @namespace tweeny
 * @brief Contains all public API types and functions for creating and managing tweens.
 *
 * This namespace provides the builder pattern API (from(), tweeny_builder), the main
 * tween class template, easing functions, and event types. All user-facing functionality
 * is contained within this namespace to avoid naming conflicts.
 */
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
      explicit tweeny_builder(FirstValue firstComponent, RemainingValues... remainingComponents) {
        key_frames.emplace_back(firstComponent, remainingComponents...);
      }

      explicit tweeny_builder(key_frames_t && frames) : key_frames(std::move(frames)) {}
      explicit tweeny_builder(const key_frames_t & frames) : key_frames(frames) {}

      /**
       * @brief Adds a target keyframe to the tween.
       *
       * Specifies the destination value(s) for the animation. After calling this,
       * you can configure easing and duration with via() and during().
       *
       * @param firstComponent Target value for the first component
       * @param remainingComponents Target values for remaining components (if multi-value tween)
       * @return Builder in a configurable state (can call via(), during(), to(), or build())
       *
       * @code
       * auto t = tweeny::from(0).to(100).during(60U).build();
       * @endcode
       */
      tweeny_builder<true, FirstValue, RemainingValues...> to(const FirstValue & firstComponent, const RemainingValues &... remainingComponents) & {
        key_frames.emplace_back(firstComponent, remainingComponents...);
        return tweeny_builder<true, FirstValue, RemainingValues...>(key_frames);
      }

      /// @overload
      tweeny_builder<true, FirstValue, RemainingValues...> to(const FirstValue & firstComponent, const RemainingValues &... remainingComponents) && {
        key_frames.emplace_back(firstComponent, remainingComponents...);
        return tweeny_builder<true, FirstValue, RemainingValues...>(std::move(key_frames));
      }

    private:
      key_frames_t key_frames;
  };

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
  template <typename FirstValue, typename... RemainingValues>
  class tweeny_builder<true, FirstValue, RemainingValues...> {
    typedef std::vector<detail::key_frame<FirstValue, RemainingValues...>> key_frames_t;
    typedef tween<FirstValue, RemainingValues...> tween_t;
    static size_t constexpr value_count = 1 + sizeof...(RemainingValues);

    public:
      explicit tweeny_builder(FirstValue firstComponent, RemainingValues... remainingComponents) {
        key_frames.emplace_back(firstComponent, remainingComponents...);
      }

      explicit tweeny_builder(key_frames_t && frames) : key_frames(std::move(frames)) {}
      explicit tweeny_builder(const key_frames_t & frames) : key_frames(frames) {}

      /**
       * @brief Adds another keyframe to create multipoint animations.
       *
       * Call `to()` multiple times to create complex animations with multiple segments,
       * each with its own easing and duration.
       *
       * @param firstComponent Target value for the first component
       * @param remainingComponents Target values for remaining components
       * @return Reference to this builder for method chaining
       *
       * @code
       * // Three-point animation: 0 → 50 → 100
       * auto t = tweeny::from(0)
       *   .to(50).via(easing::quadraticOut).during(30U)
       *   .to(100).via(easing::bounceOut).during(30U)
       *   .build();
       * @endcode
       *
       * @anchor builder_to
       */
      tweeny_builder to(const FirstValue & firstComponent, const RemainingValues &... remainingComponents) & {
        key_frames.emplace_back(firstComponent, remainingComponents...);
        return tweeny_builder(key_frames);
      }

      /// @overload
      tweeny_builder to(const FirstValue & firstComponent, const RemainingValues &... remainingComponents) && {
        key_frames.emplace_back(firstComponent, remainingComponents...);
        return tweeny_builder(std::move(key_frames));
      }

      /**
       * @brief Specifies per-component easing functions for the last keyframe segment.
       *
       * Each tween component gets its own easing function. The number of easing
       * functions must match the number of tween components (compile-time checked).
       *
       * @param easing_functions One easing function per tween component
       * @return Reference to this builder for method chaining
       *
       * @code
       * // Two components with different easings
       * auto t = tweeny::from(0, 0.0f)
       *   .to(100, 50.0f)
       *   .via(easing::linear, easing::bounceOut)
       *   .during(60U)
       *   .build();
       * @endcode
       */
      template<typename... EasingFunctionTypes>
      tweeny_builder & via(EasingFunctionTypes... easing_functions) {
        static_assert(sizeof...(EasingFunctionTypes) == value_count,
                      "via() must have one easing function per tween component");
        auto & key_frame = key_frames.at(key_frames.size() - 2);
        key_frame.easing_functions = std::make_tuple(easing_functions...);
        return *this;
      }

      /**
       * @brief Specifies a single easing function for all components.
       *
       * Applies the same easing to all tween components. This is the most common usage.
       *
       * @param easing_function Easing function to apply to all components
       * @return Reference to this builder for method chaining
       *
       * @code
       * auto t = tweeny::from(0, 0.0f).to(100, 100.0f).via(easing::quadraticInOut).during(60U).build();
       * @endcode
       *
       * @anchor builder_via
       */
      template<typename EasingFunctionType>
      tweeny_builder & via(EasingFunctionType easing_function) {
        auto & key_frame = key_frames.at(key_frames.size() - 2);
        key_frame.easing_functions = detail::make_repeated_tuple<EasingFunctionType, value_count>(easing_function);
        return *this;
      }

      /**
       * @brief Specifies per-component frame durations for the last keyframe segment.
       *
       * Each component can have its own animation duration in frames. The number of
       * durations must match the number of components (compile-time checked).
       * All parameters must be uint32_t.
       *
       * @param frame_counts Duration in frames for each component
       * @return Reference to this builder for method chaining
       *
       * @code
       * // X animates over 60 frames, Y over 120 frames
       * auto t = tweeny::from(0, 0).to(100, 100).during(60U, 120U).build();
       * @endcode
       *
       * @anchor builder_during
       */
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

      /**
       * @brief Specifies a uniform frame duration for all components.
       *
       * All tween components will animate over the same number of frames.
       * This is the most common usage.
       *
       * @param frame_count Duration in frames for the animation segment
       * @return Reference to this builder for method chaining
       *
       * @code
       * // Animate from 0 to 100 over 60 frames
       * auto t = tweeny::from(0, 0).to(100, 100).during(60U).build();
       * @endcode
       */
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

      /**
       * @brief Constructs a tween object from the configured keyframes.
       *
       * Creates a tween with all configured keyframes, easings, and durations.
       * The builder can be reused to create multiple tween instances with the same
       * configuration or modified further to create variations.
       *
       * @return A tween object ready for animation
       *
       * @code
       * // Direct use (builder discarded after build)
       * auto t1 = tweeny::from(0).to(100).via(easing::linear).during(60U).build();
       *
       * // Reusable builder
       * auto builder = tweeny::from(0).to(100).via(easing::linear).during(60U);
       * auto t2 = builder.build();  // First tween
       * auto t3 = builder.build();  // Second tween with same config
       *
       * // Create variations
       * auto t4 = builder.to(200).during(120U).build();  // Extended animation
       * @endcode
       *
       * @anchor builder_build
       */
      tween_t build() const & { return tween(key_frames); }

      /// @overload
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

  /**
   * @brief Creates a new tween builder starting from the specified value(s).
   *
   * This is the entry point for creating all tweens. It deduces types automatically
   * and supports single values, multiple values, and heterogeneous types.
   *
   * @param firstComponent Initial value for the first component
   * @param remainingComponents Initial values for additional components (optional)
   * @return A builder in the initial state (must call to() next)
   *
   * @code
   * // Single value
   * auto t1 = tweeny::from(0).to(100).during(60U).build();
   *
   * // Multiple homogeneous values
   * auto t2 = tweeny::from(0, 0).to(100, 100).during(60U).build();
   *
   * // Heterogeneous types
   * auto t3 = tweeny::from(0, 0.0f, 0u).to(10, 5.0f, 100u).during(60U).build();
   * @endcode
   */
  template <typename FirstValue, typename... RemainingValues>
  tweeny_builder<false, FirstValue, RemainingValues...> from(FirstValue firstComponent, RemainingValues... remainingComponents) {
    return tweeny_builder<false, FirstValue, RemainingValues...>(firstComponent, remainingComponents...);
  }
}

#endif //TWEENY_TWEENY_H
