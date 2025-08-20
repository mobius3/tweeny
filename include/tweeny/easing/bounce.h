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

#ifndef TWEENY_EASING_BOUNCE_H
#define TWEENY_EASING_BOUNCE_H

namespace tweeny::detail {
  struct bounceOutEasing {
    template <typename T>
    static T run(float position, T start, T end) {
      T c = end - start;
      if (position < 1 / 2.75f) {
        return static_cast<T>(c * (7.5625f * position * position) + start);
      }
      if (position < 2.0f / 2.75f) {
        const float postFix = position -= 1.5f / 2.75f;
        return static_cast<T>(c * (7.5625f * (postFix) * position + .75f) + start);
      }
      if (position < 2.5f / 2.75f) {
        const float postFix = position -= 2.25f / 2.75f;
        return static_cast<T>(c * (7.5625f * postFix * position + .9375f) + start);
      }
      const float postFix = position -= (2.625f / 2.75f);
      return static_cast<T>(c * (7.5625f * postFix * position + .984375f) + start);
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };

  struct bounceInEasing {
    template <typename T>
    static T run(const float position, T start, T end) {
      return end - start - bounceOutEasing::run(1 - position, T(), (end - start)) + start;
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };

  struct bounceInOutEasing {
    template <typename T>
    static T run(const float position, T start, T end) {
      if (position < 0.5f) return static_cast<T>(bounceInEasing::run(position * 2, T(), end - start) * .5f + start);
      return static_cast<T>(bounceOutEasing::run(position * 2 - 1, T(), end - start) * .5f + (end - start) * .5f +
        start);
    }

    template <typename T>
    T operator()(float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };
}

namespace tweeny::easing {
  inline constexpr detail::bounceInEasing bounceIn{};
  inline constexpr detail::bounceOutEasing bounceOut{};
  inline constexpr detail::bounceInOutEasing bounceInOut{};
}

#endif // TWEENY_EASING_BOUNCE_H
