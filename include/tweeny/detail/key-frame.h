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

#ifndef TWEENY_KEY_FRAME_H
#define TWEENY_KEY_FRAME_H


#include <algorithm>

#include "value-container.h"

#include <cstdint>
#include <functional>
#include <tuple>

namespace tweeny::detail {
  template<typename... ValueTypes>
  /**
   * @brief Represents a key frame in a tween.
   *
   * The key_frame class encapsulates the attributes and behaviors
   * of a single frame in an animation sequence, allowing for storage
   * and manipulation of key values at specific points.
   *
   * @warning This structure is private and shouldn't be used directly
   */
  struct key_frame {
    typedef value_container_t<ValueTypes...> values_t;
    typedef std::tuple<std::function<ValueTypes(float, ValueTypes, ValueTypes)>...> value_easing_functions_t;
    typedef std::array<uint32_t, sizeof...(ValueTypes)> value_tween_frame_counts_t;

    /**
     * @brief Constructs a key_frame object initialized with provided values.
     *
     * This constructor initializes the key_frame object by setting its position to 0,
     * populating the values container with the provided values `vs...`, and initializing
     * the easing functions and tween frame counts with default values.
     *
     * @param vs The values to initialize the key_frame, passed as a parameter pack of type `ValueTypes...`.
     *           These values are stored in a container, which can either be a tuple or an array depending
     *           on their types.
     * @return A key_frame object initialized with the provided values.
     */
    explicit key_frame(ValueTypes... vs) : position(0), values{vs...}, easing_functions(), tween_frame_counts() {}


    /**
     * Holds the 'position' of the key frame within the animation sequence.
     *
     * This variable represents the position of the current key frame as an unsigned 32-bit integer.
     * It refers to the frame index at which this key frame is located
     * within the timeline of a tween.
     */
    uint32_t position;

    /**
     * @typedef values_t
     * @brief Represents a container to store values in `key_frame`.
     *
     * The `values_t` type alias is used to hold the data values associated with
     * the `key_frame` structure. The container type is determined at compile-time
     * based on the type consistency of the provided value types. If all value types
     * are the same, the container is implemented as a `std::array`. Otherwise, it
     * is implemented as a `std::tuple`.
     */
    values_t values;

    /**
     * @typedef value_easing_functions_t easing_functions
     * @brief Represents a tuple of easing function objects for each value component in a key frame.
     *
     * This variable contains easing functions used to interpolate or transform
     * individual value components over time in a tweening operation.
     * Each easing function is specified as a callable object (e.g., a lambda or function)
     * following the signature `(float progress, ValueType start, ValueType end) -> ValueType`.
     *
     * It is used within the context of the tween system to determine how intermediate
     * values between this key frame and the next are computed based on the specified easing functions.
     */
    value_easing_functions_t easing_functions;

    /**
     * An array that represents the number of frames allocated for tweening
     * each value in a key frame. The size of the array corresponds to the
     * number of values being tweened, and each entry specifies the frame
     * count for the respective value.
     *
     * This array is populated either by specifying explicit frame counts
     * for each value during a tween's construction or by using a uniform
     * frame count for all values. The highest count is used to calculate
     * the position of key frames and manage the timing of individual
     * value transitions within a tween animation.
     */
    value_tween_frame_counts_t tween_frame_counts;

    /**
     * @brief Retrieves the highest frame count from the tween_frame_counts array.
     *
     * This function searches through the tween_frame_counts array to find
     * and return the maximum frame count value.
     *
     * @return The highest frame count as an unsigned 16-bit integer.
     */
    [[nodiscard]] uint16_t highest_frame_count() const {
      return *std::max_element(tween_frame_counts.begin(), tween_frame_counts.end());
    }
  };
}

#endif //TWEENY_KEY_FRAME_H
