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

#ifndef TWEENY_TWEEN_TCC
#define TWEENY_TWEEN_TCC

#include <algorithm>
#include <cstdint>
#include <tuple>
#include <utility>

#include "detail/interpolate.h"
#include "tweeny/easing/easing.h"

namespace tweeny::detail {
  static float clampf(const float v, const float min = 0.0f, const float max = 1.0f) {
    if (v < min) return min;
    if (v > max) return max;
    return v;
  }
}

template <typename FirstValueType, typename... RemainingValueTypes>
tweeny::tween<FirstValueType, RemainingValueTypes...>::tween(const key_frames_t & key_frames_input) : key_frames(key_frames_input) { }

template <typename FirstValueType, typename... RemainingValueTypes>
tweeny::tween<FirstValueType, RemainingValueTypes...>::tween(key_frames_t & key_frames_input) : key_frames(std::move(key_frames_input)) { }

template <typename FirstValueType, typename... RemainingValueTypes>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::find_key_frame_index(uint32_t frame) -> size_t {
  std::size_t i = 0;
  while (i + 1 < key_frames.size() && frame >= key_frames[i + 1].position) { ++i; }
  return i;
}


template <typename FirstValueType, typename... RemainingValueTypes>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::step(const int32_t frames) -> tween_value_t {
  if (frames < 0) {
    const auto dec = static_cast<uint32_t>(-frames);
    if (dec > current_frame) current_frame = 0;
    else current_frame -= dec;
  } else {
    current_frame += static_cast<uint32_t>(frames);
  }

  current_value = interpolate();
  return current_value;
}

template <typename FirstValueType, typename... RemainingValueTypes>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::interpolate() -> tween_value_t {
  constexpr std::size_t ValuesCount = sizeof...(RemainingValueTypes) + 1;

  if (key_frames.empty()) {
    if constexpr (ValuesCount == 1) {
      return FirstValueType{};
    } else {
      return typename key_frame_t::values_t{};
    }
  }

  // If before or at the first key frame, return its value
  auto & first_key_frame = key_frames.front();
  if (current_frame <= first_key_frame.position) {
    const auto & v = first_key_frame.values;
    if constexpr (ValuesCount == 1) {
      return std::get<0>(v);
    } else {
      return v;
    }
  }

  std::size_t keyframe_index = find_key_frame_index(current_frame);

  // If next at or past the last key frame, return its value
  auto & last_key_frame = key_frames.back();
  if (keyframe_index + 1 >= key_frames.size()) {
    const auto & v = last_key_frame.values;
    if constexpr (ValuesCount == 1) {
      return std::get<0>(v);
    } else {
      return v;
    }
  }

  const key_frame_t & base_key_frame = key_frames[keyframe_index];
  const key_frame_t & next_key_frame = key_frames[keyframe_index + 1];

  const int64_t base_pos = base_key_frame.position;
  const uint32_t next_pos = next_key_frame.position;
  const int64_t current_frame_i64 = current_frame;

  float tweening_progress = 1.0f;
  if (next_pos > base_pos) {
    const auto numerator = static_cast<float>(current_frame_i64 - base_pos);
    const auto denominator = static_cast<float>(next_pos - base_pos);
    tweening_progress = numerator / denominator;
  }
  tweening_progress = detail::clampf(tweening_progress);

  auto values = detail::interpolate_values<FirstValueType, RemainingValueTypes...>(
    tweening_progress,
    base_key_frame,
    next_key_frame,
    std::make_index_sequence<ValuesCount>{}
  );

  if constexpr (ValuesCount == 1) {
    return std::get<0>(values);
  } else {
    return values;
  }
}

#endif //TWEENY_TWEEN_TCC
