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
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::seek(const uint32_t target_frame) -> tween_value_t {
  current_frame = target_frame;
  current_value = render(target_frame);

  invoke_listeners(seek_listeners);

  return current_value;
}

template <typename FirstValueType, typename... RemainingValueTypes>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::jump(std::size_t target_key_frame) -> tween_value_t {
  target_key_frame = std::clamp(target_key_frame, static_cast<size_t>(0), key_frames.size() - 1);
  const auto target_frame = static_cast<uint32_t>(key_frames[target_key_frame].position);
  current_frame = target_frame;
  current_value = render(target_frame);

  invoke_listeners(jump_listeners);

  return current_value;
}

template <typename FirstValueType, typename... RemainingValueTypes>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::step(const int32_t frames) -> tween_value_t {
  uint32_t target_frame = current_frame;
  if (frames < 0) {
    const auto dec = static_cast<uint32_t>(-frames);
    if (dec > target_frame) target_frame = 0;
    else target_frame -= dec;
  } else {
    target_frame += static_cast<uint32_t>(frames);
  }

  current_frame = target_frame;
  current_value = render(target_frame);

  invoke_listeners(step_listeners);

  return current_value;
}

template <typename FirstValueType, typename ... RemainingValueTypes>
template <typename Callback>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::on(event::step_t, Callback && cb) -> void {
  using result_t = std::invoke_result_t<Callback, tween&>;
  static_assert(std::is_same_v<result_t, event::response>,
                "step callback must return tweeny::event::response");
  step_listeners.emplace_back(std::forward<Callback>(cb));
}

template <typename FirstValueType, typename ... RemainingValueTypes>
template <typename Callback>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::on(event::seek_t, Callback && cb) -> void {
  using result_t = std::invoke_result_t<Callback, tween&>;
  static_assert(std::is_same_v<result_t, event::response>,
                "seek callback must return tweeny::event::response");
  seek_listeners.emplace_back(std::forward<Callback>(cb));
}

template <typename FirstValueType, typename ... RemainingValueTypes>
template <typename Callback>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::on(event::jump_t, Callback && cb) -> void {
  using result_t = std::invoke_result_t<Callback, tween&>;
  static_assert(std::is_same_v<result_t, event::response>,
                "jump callback must return tweeny::event::response");
  jump_listeners.emplace_back(std::forward<Callback>(cb));
}

template <typename FirstValueType, typename... RemainingValueTypes>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::invoke_listeners(std::vector<callback_t>& listeners) -> void {
  std::vector<std::size_t> to_remove;
  to_remove.reserve(listeners.size());

  for (std::size_t i = 0; i < listeners.size(); ++i) {
    const auto resp = listeners[i](*this);
    if (resp == event::response::unsubscribe) {
      to_remove.push_back(i);
    }
  }

  if (!to_remove.empty()) {
    using diff_t = typename std::vector<callback_t>::difference_type;
    for (auto it = to_remove.rbegin(); it != to_remove.rend(); ++it) {
      listeners.erase(listeners.begin() + static_cast<diff_t>(*it));
    }
  }
}

template <typename FirstValueType, typename... RemainingValueTypes>
auto tweeny::tween<FirstValueType, RemainingValueTypes...>::render(uint32_t target_frame) -> tween_value_t {
  constexpr std::size_t ValuesCount = sizeof...(RemainingValueTypes) + 1;

  if (target_frame == current_frame) return current_value;

  const auto as_return_value = [](const auto & val) -> tween_value_t {
    if constexpr (ValuesCount == 1) {
      return std::get<0>(val);
    } else {
      return val;
    }
  };

  if (key_frames.empty()) {
    if constexpr (ValuesCount == 1) {
      return FirstValueType{};
    } else {
      return typename key_frame_t::values_t{};
    }
  }

  auto & first_key_frame = key_frames.front();
  auto & last_key_frame = key_frames.back();

  // note to future self: we don't need to add the frame count
  // to the last_key_frame.position because there's no interpolation
  // beyond it (duh)
  target_frame = std::clamp(
    target_frame,
    first_key_frame.position,
    last_key_frame.position
  );

  if (target_frame <= first_key_frame.position) return as_return_value(first_key_frame.values);
  if (target_frame >= last_key_frame.position) return as_return_value(last_key_frame.values);

  std::size_t base_key_key_frame_idx = find_key_frame_index(target_frame);

  if (base_key_key_frame_idx + 1 >= key_frames.size()) {
    return as_return_value(last_key_frame.values);
  }

  const key_frame_t & base_key_frame = key_frames[base_key_key_frame_idx];
  const key_frame_t & next_key_frame = key_frames[base_key_key_frame_idx + 1];

  const int64_t base_kf_position = base_key_frame.position;
  const uint32_t target_kf_position = next_key_frame.position;
  const int64_t target_frame_i64 = target_frame;

  float inbetween_progress = 1.0f;
  if (target_kf_position > base_kf_position) {
    const auto numerator = static_cast<float>(target_frame_i64 - base_kf_position);
    const auto denominator = static_cast<float>(target_kf_position - base_kf_position);
    inbetween_progress = numerator / denominator;
  }
  inbetween_progress = std::clamp(inbetween_progress, 0.0f, 1.0f);

  auto values = detail::interpolate_values<FirstValueType, RemainingValueTypes...>(
    inbetween_progress,
    base_key_frame,
    next_key_frame,
    std::make_index_sequence<ValuesCount>{}
  );

  return as_return_value(values);
}

#endif //TWEENY_TWEEN_TCC
