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

#ifndef TWEENY_INTERPOLATE_H
#define TWEENY_INTERPOLATE_H
#include <cstddef>
#include <tuple>
#include <utility>

#include "key-frame.h"
#include "../easing.h"

namespace tweeny::detail {
  template <std::size_t I, typename... ValueTypes>
  static auto interpolate_one(
    float t,
    const key_frame<ValueTypes...> & base,
    const key_frame<ValueTypes...> & next
  ) -> std::remove_reference_t<decltype(std::get<I>(base.values))> {
    const auto & start = std::get<I>(base.values);
    const auto & end = std::get<I>(next.values);
    const auto & func = std::get<I>(base.easing_functions);
    if (func) return func(t, start, end);
    return easing::def(t, start, end);
  }

  template <typename... ValueTypes, std::size_t... I>
  static auto interpolate_values(
    float t,
    const key_frame<ValueTypes...> & base,
    const key_frame<ValueTypes...> & next,
    std::index_sequence<I...>
  ) -> typename key_frame<ValueTypes...>::values_t {
    using values_t = typename key_frame<ValueTypes...>::values_t;
    values_t out{};
    ((std::get<I>(out) = interpolate_one<I>(t, base, next)), ...);
    return out;
  }
}

#endif //TWEENY_INTERPOLATE_H
