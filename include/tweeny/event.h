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
 * @file event.h
 * @brief Event system for tween animation callbacks.
 *
 * This file defines event types and response codes for the tween event system.
 * Events are triggered during tween operations (step, seek, jump, complete) and
 * allow callbacks to react to animation state changes. Tag types are defined in
 * detail/event.h and instantiated here with documentation.
 *
 * @code
 * auto t = tweeny::from(0).to(100).during(60U).build();
 * t.on(tweeny::event::step, [](auto& tween) {
 *   printf("Value: %d\n", tween.peek());
 *   return tweeny::event::response::ok;
 * });
 * @endcode
 */

#ifndef TWEENY_EVENT_H
#define TWEENY_EVENT_H

#include "detail/event.h"

/**
 * @namespace tweeny::event
 * @brief Event types and response codes for tween callbacks.
 *
 * This namespace contains tag types for registering event listeners and
 * response codes for controlling callback behavior. Use these tags with
 * tween::on() to register callbacks for animation lifecycle events.
 */
namespace tweeny::event {
  /**
   * @brief Event triggered after each step() call.
   *
   * Use this event to react to frame-by-frame progression of an animation.
   * The callback receives a reference to the tween and can query its current
   * state using peek() or progress().
   *
   * Common use cases:
   * - Updating visual properties every frame
   * - Logging animation progress
   * - Synchronizing with other animations
   * - Implementing custom timing logic
   *
   * @code
   * auto tween = tweeny::from(0).to(100).during(60U).build();
   * tween.on(tweeny::event::step, [](auto& t) {
   *   printf("Current value: %d\n", t.peek());
   *   return tweeny::event::response::ok;
   * });
   *
   * tween.step(1);  // Triggers the callback
   * @endcode
   *
   * @see seek For events when jumping to specific frames
   * @see complete For events when animation finishes
   */
  inline constexpr detail::event::step_t step{};

  /**
   * @brief Event triggered after each seek() call.
   *
   * Use this event to react when the tween jumps to a specific frame position.
   * Unlike step events, seek events fire regardless of the direction or distance
   * of the movement.
   *
   * Common use cases:
   * - Scrubbing through animations
   * - Reacting to timeline jumps
   * - Updating state after non-linear navigation
   * - Synchronizing with external timeline controls
   *
   * @code
   * auto tween = tweeny::from(0).to(100).during(100U).build();
   * tween.on(tweeny::event::seek, [](auto& t) {
   *   printf("Seeked to frame with value: %d\n", t.peek());
   *   return tweeny::event::response::ok;
   * });
   *
   * tween.seek(50U);  // Triggers the callback
   * @endcode
   *
   * @see step For frame-by-frame progression events
   * @see jump For keyframe-specific navigation
   */
  inline constexpr detail::event::seek_t seek{};

  /**
   * @brief Event triggered after each jump() call.
   *
   * Use this event to react when the tween jumps to a specific keyframe by index.
   * This is particularly useful for multi-point animations where keyframes represent
   * distinct animation phases.
   *
   * Common use cases:
   * - Transitioning between animation states
   * - Triggering phase-specific logic
   * - Resetting to specific animation checkpoints
   * - Implementing state machines
   *
   * @code
   * auto tween = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
   * tween.on(tweeny::event::jump, [](auto& t) {
   *   printf("Jumped to keyframe\n");
   *   return tweeny::event::response::ok;
   * });
   *
   * tween.jump(1);  // Jump to keyframe 1, triggers callback
   * @endcode
   *
   * @see keyframeEnter For detecting keyframe transitions during playback
   * @see seek For arbitrary frame jumps
   */
  inline constexpr detail::event::jump_t jump{};

  /**
   * @brief Event triggered when the animation is at completion.
   *
   * Fires whenever progress() is >= 1.0 (100%) after a step(), seek(), or jump() call.
   * This means the callback will fire **every time** the tween is navigated to a completed
   * state, not just the first time.
   *
   * Common use cases:
   * - Cleaning up resources after animation
   * - Chaining animations sequentially
   * - Triggering completion callbacks
   * - Transitioning to next state
   * - Playing sound effects or particle effects at end
   *
   * @note The callback fires every time the tween is at completion (progress >= 1.0).
   * If you step to completion, then back, then forward to completion again, it will
   * fire both times. Use response::unsubscribe if you want one-shot behavior.
   *
   * @code
   * auto tween = tweeny::from(0).to(100).during(60U).build();
   * tween.on(tweeny::event::complete, [](auto& t) {
   *   printf("Animation at completion: %d\n", t.peek());
   *   return tweeny::event::response::unsubscribe;  // One-shot callback
   * });
   *
   * tween.step(60);   // Fires complete callback
   * tween.step(-10);  // Now progress < 1.0
   * tween.step(10);   // Would fire again, but we unsubscribed
   * @endcode
   *
   * @see step For frame-by-frame events during animation
   * @see response::unsubscribe For one-shot completion handlers
   */
  inline constexpr detail::event::complete_t complete{};

  /**
   * @brief Event triggered when entering a new keyframe segment.
   *
   * Fires when the tween transitions into a new keyframe section during playback.
   * The callback receives both the tween reference and a keyframeEnter struct
   * containing the keyframe index.
   *
   * Common use cases:
   * - Triggering phase-specific animations
   * - Playing transition sounds
   * - Updating UI to reflect animation phase
   * - Synchronizing multi-part animations
   * - Implementing animation state machines
   *
   * @note Keyframe indices are 0-based. The first keyframe is index 0, second is 1, etc.
   *
   * @code
   * auto tween = tweeny::from(0)
   *   .to(50).during(30U)
   *   .to(100).during(30U)
   *   .build();
   *
   * tween.on(tweeny::event::keyframeEnter, [](auto& t, tweeny::event::keyframeEnter evt) {
   *   printf("Entering keyframe %zu\n", evt.key_frame);
   *   return tweeny::event::response::ok;
   * });
   *
   * tween.step(31);  // Triggers: "Entering keyframe 1"
   * @endcode
   *
   * @see keyframeLeave For detecting when leaving a keyframe
   * @see keyframeEnter For the event data struct
   * @see jump For manually jumping to keyframes
   */
  inline constexpr detail::event::keyframeEnter_t keyframeEnter{};

  /**
   * @brief Event triggered when leaving a keyframe segment.
   *
   * Fires when the tween transitions out of a keyframe section during playback.
   * The callback receives both the tween reference and a keyframeLeave struct
   * containing the keyframe index being exited.
   *
   * Common use cases:
   * - Cleaning up phase-specific resources
   * - Stopping phase-specific effects
   * - Logging animation progression
   * - Implementing phase exit handlers
   * - Coordinating complex multi-segment animations
   *
   * @note Keyframe indices are 0-based. Leaving keyframe 0 means transitioning
   * from the first to the second segment.
   *
   * @code
   * auto tween = tweeny::from(0)
   *   .to(50).during(30U)
   *   .to(100).during(30U)
   *   .build();
   *
   * tween.on(tweeny::event::keyframeLeave, [](auto& t, tweeny::event::keyframeLeave evt) {
   *   printf("Leaving keyframe %zu\n", evt.key_frame);
   *   return tweeny::event::response::ok;
   * });
   *
   * tween.step(31);  // Triggers: "Leaving keyframe 0"
   * @endcode
   *
   * @see keyframeEnter For detecting when entering a keyframe
   * @see keyframeLeave For the event data struct
   */
  inline constexpr detail::event::keyframeLeave_t keyframeLeave{};

  /**
   * @brief Event triggered whenever the tween position changes.
   *
   * Fires after any step(), seek(), or jump() call. This is a convenience event
   * that consolidates all position update events into a single callback point.
   *
   * Common use cases:
   * - Updating visuals regardless of how the tween changed
   * - Monitoring all tween changes from one place
   * - Logging every position update
   * - Synchronizing with external systems
   * - Implementing universal change handlers
   *
   * @note This event fires **after** the specific event (step, seek, or jump) and
   * **before** the complete event if applicable.
   *
   * @code
   * auto tween = tweeny::from(0).to(100).during(60U).build();
   * tween.on(tweeny::event::update, [](auto& t) {
   *   printf("Tween updated to: %d\n", t.peek());
   *   return tweeny::event::response::ok;
   * });
   *
   * tween.step(10);  // Triggers update
   * tween.seek(50U); // Triggers update
   * tween.jump(1);   // Triggers update
   * @endcode
   *
   * @see step For frame-by-frame updates
   * @see seek For arbitrary frame jumps
   * @see jump For keyframe jumps
   */
  inline constexpr detail::event::update_t update{};
}

#endif //TWEENY_EVENT_H
