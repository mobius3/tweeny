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
 * @file tween.h
 * @brief Core tween class for frame-based animation.
 *
 * This file defines the tween class, which represents an animation between keyframes.
 * Tweens interpolate values over time using configurable easing functions and support
 * event listeners for animation lifecycle events.
 *
 * @code
 * auto t = tweeny::from(0).to(100).during(60U).build();
 * t.step(1);              // Advance one frame
 * auto val = t.peek();    // Get current value
 * float p = t.progress(); // Get completion (0.0-1.0)
 * @endcode
 */

#ifndef TWEENY_TWEEN_H
#define TWEENY_TWEEN_H

#include <vector>
#include <cstdint>
#include <cstddef>
#include <functional>

#include "detail/key-frame.h"
#include "detail/tween-value.h"
#include "detail/event.h"

namespace tweeny {
  /**
   * @brief A tween represents an animation between keyframes.
   *
   * Tweens interpolate values over discrete frames using configurable easing functions.
   * They maintain internal state (current frame and value) and support event listeners
   * for animation events.
   *
   * @tparam FirstValueType Type of the first animated value
   * @tparam RemainingValueTypes Types of additional animated values (for multi-value tweens)
   *
   * @note For single values, tween_value_t is the value type directly.
   *       For multiple values, tween_value_t is std::tuple<FirstValueType, RemainingValueTypes...>
   */
  template<typename FirstValueType, typename... RemainingValueTypes>
  class tween {
    typedef detail::key_frame<FirstValueType, RemainingValueTypes...> key_frame_t;
    typedef std::vector<key_frame_t> key_frames_t;

    public:
      /**
       * @brief The type returned by navigation and query methods.
       *
       * For single-value tweens: the value type itself.
       * For multi-value tweens: std::tuple of all value types.
       */
      using tween_value_t = detail::tween_value_t<FirstValueType, RemainingValueTypes...>;

      /**
       * @brief Constructs a tween from keyframes (use builder API instead).
       * @internal Users should use tweeny::from() to create tweens.
       */
      explicit tween(const key_frames_t & key_frames_input);

      /// @overload
      explicit tween(key_frames_t && key_frames_input);

      /**
       * @brief Seeks to a specific frame in the animation.
       *
       * Jumps directly to the target frame, updating the tween's current position and value.
       * Clamped to [first_frame, last_frame]. Triggers event::seek listeners.
       *
       * @param target_frame Absolute frame number to seek to
       * @return Interpolated value at the target frame
       *
       * @code
       * auto t = tweeny::from(0).to(100).during(100U).build();
       * t.seek(50U);  // Jump to frame 50 (value: 50)
       * t.seek(0U);   // Jump back to start
       * @endcode
       */
      auto seek(uint32_t target_frame) -> tween_value_t;

      /**
       * @brief Jumps to a specific keyframe index.
       *
       * Moves the tween to the exact position of a keyframe. Useful for resetting to
       * known points or implementing discrete state animations. Triggers event::jump listeners.
       *
       * @param target_key_frame Zero-based keyframe index (clamped to valid range)
       * @return Value at the target keyframe
       *
       * @code
       * auto t = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
       * t.jump(0);  // Jump to first keyframe (value: 0)
       * t.jump(1);  // Jump to second keyframe (value: 50)
       * t.jump(2);  // Jump to third keyframe (value: 100)
       * @endcode
       */
      auto jump(std::size_t target_key_frame) -> tween_value_t;

      /**
       * @brief Advances or rewinds the animation by a frame delta.
       *
       * Moves the tween forward (positive) or backward (negative) by the specified number
       * of frames. Clamped to valid frame range. Triggers event::step listeners.
       *
       * @param frames Number of frames to move (negative values step backward)
       * @return Interpolated value at the new frame
       *
       * @code
       * auto t = tweeny::from(0).to(100).during(100U).build();
       * t.step(10);   // Advance 10 frames (value: 10)
       * t.step(5);    // Advance 5 more frames (value: 15)
       * t.step(-3);   // Rewind 3 frames (value: 12)
       * @endcode
       */
      auto step(int32_t frames) -> tween_value_t;

      /**
       * @brief Returns the current interpolated value without changing state.
       *
       * Non-mutating query of the tween's current value. Does not trigger events
       * or modify the tween's position.
       *
       * @return Current interpolated value
       *
       * @code
       * auto t = tweeny::from(0).to(100).during(100U).build();
       * t.step(25);
       * auto val = t.peek();  // Returns 25, doesn't change state
       * @endcode
       */
      [[nodiscard]] auto peek() const -> tween_value_t;

      /**
       * @brief Queries the interpolated value at any frame without changing state.
       *
       * Previews what the value would be at the target frame without moving the tween.
       * Useful for scrubbing, previewing, or inspecting the animation curve.
       * Does not trigger events.
       *
       * @param target_frame Frame to query (clamped to valid range)
       * @return Interpolated value at the target frame
       *
       * @code
       * auto t = tweeny::from(0).to(100).during(100U).build();
       * auto midpoint = t.peek(50U);  // Preview value at frame 50 (returns 50)
       * auto start = t.peek(0U);      // Preview start value (returns 0)
       * // Tween still at frame 0, not moved
       * @endcode
       */
      [[nodiscard]] auto peek(uint32_t target_frame) const -> tween_value_t;

      /**
       * @brief Returns the animation completion percentage.
       *
       * Calculates progress as (current_frame - first_frame) / total_frames.
       * Returns a value in the range [0.0, 1.0].
       *
       * @return Progress percentage (0.0 = start, 1.0 = complete)
       *
       * @code
       * auto t = tweeny::from(0).to(100).during(100U).build();
       * t.step(25);
       * printf("%.0f%% complete\n", t.progress() * 100.0f);  // "25% complete"
       *
       * // Check if animation is done
       * if (t.progress() >= 1.0f) {
       *   printf("Animation complete!\n");
       * }
       * @endcode
       */
      [[nodiscard]] auto progress() const -> float;

      /**
       * @brief Registers a callback for step() events.
       *
       * The callback is invoked after each step() call. It receives a reference to
       * the tween and must return event::response::ok to continue receiving events,
       * or event::response::unsubscribe to auto-remove.
       *
       * @param cb Callback with signature: event::response(tween&)
       *
       * @code
       * auto t = tweeny::from(0).to(100).during(100U).build();
       * t.on(event::step, [](auto& tween) {
       *   printf("Stepped to: %d\n", tween.peek());
       *   return event::response::ok;
       * });
       * t.step(10);  // Prints: "Stepped to: 10"
       * @endcode
       */
      template <typename Callback> auto on(detail::event::step_t, Callback&& cb) -> void ;

      /**
       * @brief Registers a callback for seek() events.
       *
       * The callback is invoked after each seek() call. Same signature and behavior as step events.
       *
       * @param cb Callback with signature: event::response(tween&)
       *
       * @code
       * t.on(event::seek, [](auto& tween) {
       *   printf("Seeked to: %d\n", tween.peek());
       *   return event::response::ok;
       * });
       * @endcode
       */
      template <typename Callback> auto on(detail::event::seek_t, Callback&& cb) -> void ;

      /**
       * @brief Registers a callback for jump() events.
       *
       * The callback is invoked after each jump() call. Same signature and behavior as step events.
       *
       * @param cb Callback with signature: event::response(tween&)
       *
       * @code
       * t.on(event::jump, [](auto& tween) {
       *   printf("Jumped to keyframe\n");
       *   return event::response::ok;
       * });
       * @endcode
       */
      template <typename Callback> auto on(detail::event::jump_t, Callback&& cb) -> void ;

      /**
       * @brief Registers a callback for animation completion.
       *
       * The callback is invoked when the tween reaches the last frame (progress >= 1.0).
       * Triggered by step(), seek(), or jump() when they result in completion.
       *
       * @param cb Callback with signature: event::response(tween&)
       *
       * @code
       * auto t = tweeny::from(0).to(100).during(100U).build();
       * t.on(event::complete, [](auto& tween) {
       *   printf("Animation complete!\n");
       *   return event::response::ok;
       * });
       * t.seek(100U);  // Triggers complete event
       * @endcode
       */
      template <typename Callback> auto on(detail::event::complete_t, Callback&& cb) -> void ;

      /**
       * @brief Registers a callback for entering a keyframe.
       *
       * The callback is invoked when the tween transitions into a new keyframe section.
       * Receives the tween reference and event data containing the keyframe index.
       *
       * @param cb Callback with signature: event::response(tween&, event::keyframeEnter)
       *
       * @code
       * auto t = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
       * t.on(event::keyframeEnter, [](auto& tween, auto evt) {
       *   printf("Entered keyframe %zu\n", evt.key_frame);
       *   return event::response::ok;
       * });
       * t.step(31);  // Triggers: "Entered keyframe 1"
       * @endcode
       */
      template <typename Callback> auto on(detail::event::keyframeEnter_t, Callback&& cb) -> void ;

      /**
       * @brief Registers a callback for leaving a keyframe.
       *
       * The callback is invoked when the tween transitions out of a keyframe section.
       * Receives the tween reference and event data containing the keyframe index.
       *
       * @param cb Callback with signature: event::response(tween&, event::keyframeLeave)
       *
       * @code
       * auto t = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
       * t.on(event::keyframeLeave, [](auto& tween, auto evt) {
       *   printf("Left keyframe %zu\n", evt.key_frame);
       *   return event::response::ok;
       * });
       * t.step(31);  // Triggers: "Left keyframe 0"
       * @endcode
       */
      template <typename Callback> auto on(detail::event::keyframeLeave_t, Callback&& cb) -> void ;

      /**
       * @brief Registers a callback for any position update (step, seek, or jump).
       *
       * The callback is invoked after step(), seek(), or jump() calls. This is a convenience
       * event for monitoring all position changes from a single callback.
       *
       * @param cb Callback with signature: event::response(tween&)
       *
       * @code
       * auto t = tweeny::from(0).to(100).during(60U).build();
       * t.on(event::update, [](auto& tween) {
       *   printf("Tween updated to: %d\n", tween.peek());
       *   return event::response::ok;
       * });
       * t.step(10);  // Triggers update
       * t.seek(50U); // Triggers update
       * @endcode
       */
      template <typename Callback> auto on(detail::event::update_t, Callback&& cb) -> void ;

    private:
      using callback_t = std::function<event::response(tween&)>;
      using keyframe_enter_callback_t = std::function<event::response(tween&, struct event::keyframeEnter)>;
      using keyframe_leave_callback_t = std::function<event::response(tween&, struct event::keyframeLeave)>;

      key_frames_t key_frames;
      uint32_t current_frame = 0;
      tween_value_t current_value;
      std::size_t current_keyframe_index = 0;
      std::vector<callback_t> step_listeners;
      std::vector<callback_t> seek_listeners;
      std::vector<callback_t> jump_listeners;
      std::vector<callback_t> complete_listeners;
      std::vector<callback_t> update_listeners;
      std::vector<keyframe_enter_callback_t> keyframe_enter_listeners;
      std::vector<keyframe_leave_callback_t> keyframe_leave_listeners;

      auto invoke_listeners(std::vector<callback_t>& listeners) -> void;
      auto invoke_keyframe_listeners(std::size_t old_keyframe_index, std::size_t new_keyframe_index) -> void;
      auto render(uint32_t target_frame) const -> tween_value_t;
      [[nodiscard]] auto find_key_frame_index(uint32_t frame) const -> std::size_t;
  };
}

#include "tween.tcc"

#endif //TWEENY_TWEEN_H
