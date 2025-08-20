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

#ifndef TWEENY_EASING_ELASTIC_H
#define TWEENY_EASING_ELASTIC_H

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace tweeny::detail {
  struct elasticInEasing {
    template <typename T>
    static T run(float position, T start, T end) {
      if (position <= 0.00001f) return start;
      if (position >= 0.999f) return end;
      const float p = .3f;
      auto a = end - start;
      const float s = p / 4;
      const float postFix = a * powf(2, 10 * (position -= 1));
      return static_cast<T>(-(postFix * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p)) + start);
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };

  struct elasticOutEasing {
    template <typename T>
    static T run(const float position, T start, T end) {
      if (position <= 0.00001f) return start;
      if (position >= 0.999f) return end;
      float p = .3f;
      auto a = end - start;
      float s = p / 4;
      return static_cast<T>(a * powf(2, -10 * position) * sinf(
        (position - s) * (2 * static_cast<float>(M_PI)) / p
      ) + end);
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };

  struct elasticInOutEasing {
    template <typename T>
    static T run(float position, T start, T end) {
      if (position <= 0.00001f) return start;
      if (position >= 0.999f) return end;
      position *= 2;
      const float p = .3f * 1.5f;
      auto a = end - start;
      const float s = p / 4;
      float postFix;

      if (position < 1) {
        postFix = a * powf(2, 10 * (position -= 1));
        return static_cast<T>(-0.5f * (postFix * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p)) + start);
      }
      postFix = a * powf(2, -10 * (position -= 1));
      return static_cast<T>(postFix * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p) * .5f + end);
    }

    template <typename T>
    T operator()(const float position, T start, T end) const {
      return run<T>(position, start, end);
    }
  };
}

namespace tweeny::easing {
  inline constexpr detail::elasticInEasing elasticIn{};
  inline constexpr detail::elasticOutEasing elasticOut{};
  inline constexpr detail::elasticInOutEasing elasticInOut{};
}

#endif // TWEENY_EASING_ELASTIC_H
