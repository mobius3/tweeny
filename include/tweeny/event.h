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
 * allow callbacks to react to animation state changes.
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

#include <cstddef>

/**
 * @namespace tweeny::event
 * @brief Event types and response codes for tween callbacks.
 *
 * This namespace contains tag types for registering event listeners and
 * response codes for controlling callback behavior.
 */
namespace tweeny::event {
  /**
   * @brief Event data passed when entering a new keyframe.
   *
   * This event is triggered when the tween transitions into a new keyframe section,
   * providing the index of the keyframe being entered.
   *
   * @code
   * auto t = tweeny::from(0).to(100).during(60U).build();
   * t.on(tweeny::event::keyframeEnter, [](auto& tween, tweeny::event::keyframeEnter evt) {
   *   std::cout << "Entered keyframe " << evt.key_frame << std::endl;
   *   return tweeny::event::response::ok;
   * });
   * @endcode
   */
  struct keyframeEnter {
    size_t key_frame;
    explicit keyframeEnter(const size_t key_frame_input) : key_frame(key_frame_input) {}
  };

  /**
   * @brief Event data passed when leaving a keyframe.
   *
   * This event is triggered when the tween transitions out of a keyframe section,
   * providing the index of the keyframe being exited.
   *
   * @code
   * auto t = tweeny::from(0).to(100).during(60U).build();
   * t.on(tweeny::event::keyframeLeave, [](auto& tween, tweeny::event::keyframeLeave evt) {
   *   std::cout << "Left keyframe " << evt.key_frame << std::endl;
   *   return tweeny::event::response::ok;
   * });
   * @endcode
   */
  struct keyframeLeave {
    size_t key_frame;
    explicit keyframeLeave(const size_t key_frame_input) : key_frame(key_frame_input) {}
  };

  /**
   * @brief Tag type for step events.
   *
   * Used with tween::on() to register callbacks triggered after step() calls.
   *
   * @code
   * t.on(tweeny::event::step, [](auto& tween) {
   *   return tweeny::event::response::ok;
   * });
   * @endcode
   *
   * @anchor step
   */
  inline struct step_t {} step;

  /**
   * @brief Tag type for seek events.
   *
   * Used with tween::on() to register callbacks triggered after seek() calls.
   *
   * @code
   * t.on(tweeny::event::seek, [](auto& tween) {
   *   return tweeny::event::response::ok;
   * });
   * @endcode
   */
  inline struct seek_t {} seek;

  /**
   * @brief Tag type for jump events.
   *
   * Used with tween::on() to register callbacks triggered after jump() calls.
   *
   * @code
   * t.on(tweeny::event::jump, [](auto& tween) {
   *   return tweeny::event::response::ok;
   * });
   * @endcode
   */
  inline struct jump_t {} jump;

  /**
   * @brief Tag type for update events.
   * @internal Currently unused - reserved for future implementation.
   */
  inline struct update_t {} update;

  /**
   * @brief Tag type for completion events.
   *
   * Used with tween::on() to register callbacks triggered when progress reaches 1.0.
   * Fires after step(), seek(), or jump() when the animation completes.
   *
   * @code
   * t.on(tweeny::event::complete, [](auto& tween) {
   *   printf("Animation done!\n");
   *   return tweeny::event::response::ok;
   * });
   * @endcode
   */
  inline struct complete_t {} complete;

  /**
   * @brief Tag type for the keyframeEnter event.
   *
   * Use this tag with tween::on() to register a callback that fires when the tween
   * enters a new keyframe section.
   *
   * @code
   * auto t = tweeny::from(0).to(100).during(60U).build();
   * t.on(tweeny::event::keyframeEnter, [](auto& tween, tweeny::event::keyframeEnter evt) {
   *   std::cout << "Entered keyframe " << evt.key_frame << std::endl;
   *   return tweeny::event::response::ok;
   * });
   * @endcode
   */
  inline struct keyframeEnter_t {} keyframeEnter;

  /**
   * @brief Tag type for the keyframeLeave event.
   *
   * Use this tag with tween::on() to register a callback that fires when the tween
   * leaves a keyframe section.
   *
   * @code
   * auto t = tweeny::from(0).to(100).during(60U).build();
   * t.on(tweeny::event::keyframeLeave, [](auto& tween, tweeny::event::keyframeLeave evt) {
   *   std::cout << "Left keyframe " << evt.key_frame << std::endl;
   *   return tweeny::event::response::ok;
   * });
   * @endcode
   */
  inline struct keyframeLeave_t {} keyframeLeave;

  /**
   * @brief Response codes returned by event callbacks.
   *
   * Controls whether a callback continues receiving events or is automatically removed.
   */
  enum class response {
    /**
     * @brief Continue receiving events.
     *
     * The callback remains registered and will be invoked on future events.
     */
    ok = 0,

    /**
     * @brief Unsubscribe after this callback.
     *
     * The callback is automatically removed after returning and will not
     * receive future events. Useful for one-shot callbacks.
     *
     * @code
     * t.on(tweeny::event::complete, [](auto& tween) {
     *   printf("Animation done!\n");
     *   return tweeny::event::response::unsubscribe;  // Remove this callback
     * });
     * @endcode
     */
    unsubscribe = 1,
  };
}

#endif //TWEENY_EVENT_H
