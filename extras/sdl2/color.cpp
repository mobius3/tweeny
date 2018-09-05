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

#include <cmath>
#include "color.h"
#define tweeny_max(a, b) (((a) > (b)) ? (a) : (b))
#define tweeny_min(a, b) (((a) > (b)) ? (b) : (a))

using namespace tweeny::extras;

struct frgb {
  float r, g, b;
};

tweeny::extras::sdl2::color tweeny::extras::sdl2::color::black{sdl2::rgba{0, 0, 0, 255}};
tweeny::extras::sdl2::color tweeny::extras::sdl2::color::white{sdl2::rgba{255, 255, 255, 255}};
tweeny::extras::sdl2::color tweeny::extras::sdl2::color::red{sdl2::rgba{255, 0, 0, 255}};
tweeny::extras::sdl2::color tweeny::extras::sdl2::color::green{sdl2::rgba{0, 255, 0, 255}};
tweeny::extras::sdl2::color tweeny::extras::sdl2::color::blue{sdl2::rgba{0, 0, 255, 255}};
tweeny::extras::sdl2::color tweeny::extras::sdl2::color::yellow{sdl2::rgba{255, 255, 0, 255}};

static sdl2::rgba hsv2rgba(const sdl2::hsv & hsv) {

  float      hh, p, q, t, ff;
  long        i;
  frgb         out = {0, 0, 0};
  sdl2::rgba ret;
  ret.a = hsv.a;

  if(hsv.s <= 0.0) {
    ret.r = ret.g = ret.b = static_cast<unsigned char>(hsv.v * 255);
    return ret;
  }

  hh = hsv.h;
  if(hh >= 360.0f) hh = 0.0f;
  hh /= 60.0f;
  i = (long)hh;
  ff = hh - i;
  p = hsv.v * (1.0f - hsv.s);
  q = hsv.v * (1.0f - (hsv.s * ff));
  t = hsv.v * (1.0f - (hsv.s * (1.0f - ff)));

  switch(i) {
    case 0:
      out.r = hsv.v;
      out.g = t;
      out.b = p;
      break;
    case 1:
      out.r = q;
      out.g = hsv.v;
      out.b = p;
      break;
    case 2:
      out.r = p;
      out.g = hsv.v;
      out.b = t;
      break;

    case 3:
      out.r = p;
      out.g = q;
      out.b = hsv.v;
      break;
    case 4:
      out.r = t;
      out.g = p;
      out.b = hsv.v;
      break;
    case 5:
    default:
      out.r = hsv.v;
      out.g = p;
      out.b = q;
      break;
  }

  ret.r = static_cast<unsigned char>(out.r * 255);
  ret.g = static_cast<unsigned char>(out.g * 255);
  ret.b = static_cast<unsigned char>(out.b * 255);
  ret.a = hsv.a;
  return ret;
}

tweeny::extras::sdl2::color::color(const struct hsv & hsv) noexcept {

}

tweeny::extras::sdl2::rgba tweeny::extras::sdl2::color::rgba() const {
  return { r, g, b, a };
}

tweeny::extras::sdl2::color::color(const struct rgba & rgb) noexcept
  : r(rgb.r)
  , g(rgb.g)
  , b(rgb.b)
  , a(rgb.a)
  { }

tweeny::extras::sdl2::color::color() noexcept
: r(0), g(0), b(0), a(0) { }

tweeny::extras::sdl2::color &
tweeny::extras::sdl2::color::operator-=(const tweeny::extras::sdl2::color & other) {
  auto hsvA = hsv(), hsvB = other.hsv();
  hsvA.h -= hsvB.h;
  if (hsvA.h < 0) hsvA.h += 360;
  *this = hsvA;
  return *this;
}

tweeny::extras::sdl2::color &
tweeny::extras::sdl2::color::operator=(const sdl2::rgba & rgba) {
  r = rgba.r;
  g = rgba.g;
  b = rgba.b;
  a = rgba.a;
  return *this;
}

tweeny::extras::sdl2::color &
tweeny::extras::sdl2::color::operator=(const sdl2::hsv & hsv) {
  this->operator=(hsv2rgba(hsv));
  return *this;
}

sdl2::hsv tweeny::extras::sdl2::color::hsv() const {
  sdl2::hsv out;
  float r1 = r / 255.0f, g1 = g / 255.0f, b1 = b / 255.0f;
  float min = tweeny_min(r1, tweeny_min(g1, b1)),
    max = tweeny_max(r1, tweeny_max(g1, b1)), delta;

  out.v = max; //v
  delta = max - min;
  if (delta < 0.00001) {
    out.s = 0;
    out.h = 0; // undefined, maybe nan?
    return out;
  }

  if (max > 0.0) {
    out.s = (delta / max); // s
  } else {
    // if max is 0, then r = g = b = 0, s = 0, h is undefined
    out.s = 0.0;
    out.h = NAN; // its now undefined
    return out;
  }
  if (r1 >= max) out.h = (g1 - b1) / delta; // between yellow & magenta
  else if (g1 >= max)  out.h = 2.0f + (b1 - r1) / delta; // between cyan & yellow
  else out.h = 4.0f + (r1 - g1) / delta;  // between magenta & cyan
  out.h *= 60.0; // degrees
  if (out.h < 0.0) out.h += 360.0;
  out.a = a;
  return out;
}

sdl2::color & sdl2::color::operator*=(const float f) {
  auto asHsv = hsv();
  asHsv.h *= f;
  if (asHsv.h > 360) asHsv.h -= 360;
  if (asHsv.h < 0) asHsv.h += 360;
  operator=(asHsv);
  return *this;
}

sdl2::color & sdl2::color::operator+=(const sdl2::color & other) {
  auto hsvA = hsv(), hsvB = other.hsv();
  hsvA.h += hsvB.h;
  if (hsvA.h > 360) hsvA.h -= 360;
  *this = hsvA;
  return *this;
}

sdl2::color & sdl2::color::operator/=(float f) {
  auto asHsv = hsv();
  asHsv.h /= f;
  operator=(asHsv);
  return *this;
}

std::ostream &
tweeny::extras::sdl2::operator<<(std::ostream & os, const tweeny::extras::sdl2::color & c) {
  return os << "color(" <<
            static_cast<unsigned>(c.r) << ", " <<
            static_cast<unsigned>(c.g) << ", " <<
            static_cast<unsigned>(c.b) << ", " <<
            static_cast<unsigned>(c.a) <<
            ")";
}

sdl2::color sdl2::operator-(const sdl2::color & a, const sdl2::color & b) {
  color r = a;
  r -= b;
  return r;
}

sdl2::color sdl2::operator*(const color & a, float f) {
  color r = a;
  r *= f;
  return r;
}

sdl2::color sdl2::operator+(const sdl2::color & a, const sdl2::color & b) {
  color r = a;
  r += b;
  return r;
}

sdl2::color sdl2::operator-(const sdl2::color & a) {
  color r = a;
  hsv asHsv = a.hsv();
  asHsv.h -= 180;
  if (asHsv.h < 0) asHsv.h += 360;
  r = asHsv;
  return r;
}

sdl2::color sdl2::operator/(const sdl2::color & a, float f) {
  color r = a;
  r /= f;
  return r;
}
