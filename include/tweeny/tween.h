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

#ifndef TWEENY_TWEEN_H
#define TWEENY_TWEEN_H
#include <vector>
#include <cstdint>
#include <cstddef>

#include "detail/key-frame.h"
#include "detail/tween-value.h"

namespace tweeny {
  template<typename FirstValueType, typename... RemainingValueTypes>
  class tween {
    typedef detail::key_frame<FirstValueType, RemainingValueTypes...> key_frame_t;
    typedef std::vector<key_frame_t> key_frames_t;

    public:
      using tween_value_t = detail::tween_value_t<FirstValueType, RemainingValueTypes...>;

      explicit tween(const key_frames_t & key_frames_input);
      explicit tween(key_frames_t & key_frames_input);

      auto step(int32_t frames) -> tween_value_t;

    private:
      key_frames_t key_frames;
      uint32_t current_frame = 0;
      tween_value_t current_value;

      auto interpolate() -> tween_value_t;
      auto find_key_frame_index(uint32_t frame) -> std::size_t;
  };
}

#include "tween.tcc"

#endif //TWEENY_TWEEN_H
