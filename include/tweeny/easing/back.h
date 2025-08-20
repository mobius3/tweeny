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

#ifndef TWEENY_EASING_BACK_H
#define TWEENY_EASING_BACK_H

namespace tweeny::detail {
  struct backInEasing {
    template <typename T>
    static T run(float position, T start, T end) {
      constexpr float s = 1.70158f;
      float postFix = position;
      return static_cast<T>((end - start) * postFix * position * ((s + 1) * position - s) + start);
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };

  struct backOutEasing {
    template <typename T>
    static T run(float position, T start, T end) {
      constexpr float s = 1.70158f;
      position -= 1;
      return static_cast<T>((end - start) * ((position) * position * ((s + 1) * position + s) + 1) + start);
    }

    template <typename T>
    T operator()(float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };

  struct backInOutEasing {
    template <typename T>
    static T run(float position, T start, T end) {
      float s = 1.70158f;
      float t = position;
      auto b = start;
      auto c = end - start;
      constexpr float d = 1;
      s *= 1.525f;
      if ((t /= d / 2) < 1) return static_cast<T>(c / 2 * (t * t * ((s + 1) * t - s)) + b);
      const float postFix = t -= 2;
      return static_cast<T>(c / 2 * (postFix * t * ((s + 1) * t + s) + 2) + b);
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };
}

namespace tweeny::easing {
  inline constexpr detail::backInEasing backIn{};
  inline constexpr detail::backOutEasing backOut{};
  inline constexpr detail::backInOutEasing backInOut{};
}

#endif // TWEENY_EASING_BACK_H
