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

#ifndef TWEENY_DETAIL_EVENT_H
#define TWEENY_DETAIL_EVENT_H

#include <cstddef>

namespace tweeny::detail::event {
  /**
   * @brief Tag type for step events.
   * @internal Implementation detail - users should use tweeny::event::step
   */
  struct step_t {};

  /**
   * @brief Tag type for seek events.
   * @internal Implementation detail - users should use tweeny::event::seek
   */
  struct seek_t {};

  /**
   * @brief Tag type for jump events.
   * @internal Implementation detail - users should use tweeny::event::jump
   */
  struct jump_t {};

  /**
   * @brief Tag type for completion events.
   * @internal Implementation detail - users should use tweeny::event::complete
   */
  struct complete_t {};

  /**
   * @brief Tag type for keyframeEnter events.
   * @internal Implementation detail - users should use tweeny::event::keyframeEnter
   */
  struct keyframeEnter_t {};

  /**
   * @brief Tag type for keyframeLeave events.
   * @internal Implementation detail - users should use tweeny::event::keyframeLeave
   */
  struct keyframeLeave_t {};

  /**
   * @brief Tag type for update events.
   * @internal Implementation detail - users should use tweeny::event::update
   */
  struct update_t {};
}

namespace tweeny::event {
  /**
   * @brief Event data passed when entering a new keyframe.
   *
   * This event is triggered when the tween transitions into a new keyframe section,
   * providing the index of the keyframe being entered.
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
   */
  struct keyframeLeave {
    size_t key_frame;
    explicit keyframeLeave(const size_t key_frame_input) : key_frame(key_frame_input) {}
  };

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
     */
    unsubscribe = 1,
  };
}

#endif // TWEENY_DETAIL_EVENT_H
