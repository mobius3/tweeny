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

#ifndef TWEENY_EASING_QUINTIC_H
#define TWEENY_EASING_QUINTIC_H

namespace tweeny::detail {
  struct quinticInEasing {
    template <typename T>
    static T run(const float position, T start, T end) {
      return static_cast<T>((end - start) * position * position * position * position * position + start);
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };

  struct quinticOutEasing {
    template <typename T>
    static T run(float position, T start, T end) {
      position--;
      return static_cast<T>((end - start) * (position * position * position * position * position + 1) + start);
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };

  struct quinticInOutEasing {
    template <typename T>
    static T run(float position, T start, T end) {
      position *= 2;
      if (position < 1) {
        return static_cast<T>((end - start) / 2 * (position * position * position * position * position) + start);
      }
      position -= 2;
      return static_cast<T>((end - start) / 2 * (position * position * position * position * position + 2) + start);
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };
}

namespace tweeny::easing {
  inline constexpr detail::quinticInEasing quinticIn{};
  inline constexpr detail::quinticOutEasing quinticOut{};
  inline constexpr detail::quinticInOutEasing quinticInOut{};
}

#endif // TWEENY_EASING_QUINTIC_H
