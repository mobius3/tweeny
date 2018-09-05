/*
 This file is part of the Tweeny library.

 Copyright (c) 2016-2018 Leonardo G. Lucena de Freitas
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

#ifndef TWEENY_SDL2_COLOR_H
#define TWEENY_SDL2_COLOR_H

#include <ostream>

namespace tweeny {
  namespace extras {
    namespace sdl2 {
      struct rgba { unsigned char r = 0, g = 0, b = 0, a = 0; };
      struct hsv { float h = 0, s = 0, v = 0; unsigned char a = 0; };

      struct color {

        static color black;
        static color white;
        static color red;
        static color green;
        static color blue;
        static color yellow;

        unsigned char r = 0, g = 0, b = 0, a = 0;

        explicit color(const hsv & hsv) noexcept;
        explicit color(const rgba & rgb) noexcept;
        color() noexcept;

        sdl2::rgba rgba() const;
        sdl2::hsv hsv() const;

        color & operator=(const sdl2::rgba & rgba);
        color & operator=(const sdl2::hsv & hsv);
        color & operator-=(const color & other);
        color & operator+=(const color & other);
        color & operator*=(float f);
        color & operator/=(float f);
      };
      std::ostream & operator<<(std::ostream & os, color const & c);
      color operator-(const color & a, const color & b);
      color operator-(const color & a);
      color operator+(const color & a, const color & b);
      color operator*(const color & a, float f);
      color operator/(const color & a, float f);
    }
  }
}

#endif //TWEENY_SDL2_COLOR_H
