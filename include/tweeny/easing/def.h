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

#ifndef TWEENY_EASING_DEF_H
#define TWEENY_EASING_DEF_H

#include <type_traits>
#include <cmath>
#include <utility>

namespace tweeny::detail {
  template <class...> struct voidify {
    using type = void;
  };

  template <class... Ts> using void_t = typename voidify<Ts...>::type;

  template <class, class = void>
  struct supports_arithmetic_operations : std::false_type {};

  template <class T>
  struct supports_arithmetic_operations<T, void_t<
                                          decltype(std::declval<T>() + std::declval<T>()),
                                          decltype(std::declval<T>() - std::declval<T>()),
                                          decltype(std::declval<T>() * std::declval<T>()),
                                          decltype(std::declval<T>() * std::declval<float>()),
                                          decltype(std::declval<float>() * std::declval<T>())
                                        >> : std::true_type {};

  struct defaultEasing {
    template <typename T>
    static std::enable_if_t<std::is_integral_v<T>, T> run(float position, T start, T end) {
      return static_cast<T>(roundf((end - start) * position + start));
    }

    template <typename T>
    static typename std::enable_if<supports_arithmetic_operations<T>::value && !std::is_integral<T>::value, T>::type
      run(float position, T start, T end) {
      return static_cast<T>((end - start) * position + start);
    }

    template <typename T>
    static std::enable_if_t<!supports_arithmetic_operations<T>::value, T> run(float /*position*/, T start, T /*end*/) {
      return start;
    }

    template <typename T>
    T operator()(float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };
}

namespace tweeny::easing {
  inline constexpr detail::defaultEasing def{};
}

#endif // TWEENY_EASING_DEF_H
