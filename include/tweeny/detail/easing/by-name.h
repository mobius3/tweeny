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

#ifndef TWEENY_DETAIL_EASING_BY_NAME_H
#define TWEENY_DETAIL_EASING_BY_NAME_H

#include <stdexcept>
#include <string>
#include <string_view>

namespace tweeny::easing {

/**
 * @brief Callable easing selected by name at runtime.
 *
 * Holds only an internal id (not the name string). Construct via @ref byName.
 */
struct byNameEasing {
private:
  enum class id {
    linear,
    def,
    stepped,
    quadraticIn,
    quadraticOut,
    quadraticInOut,
    cubicIn,
    cubicOut,
    cubicInOut,
    quarticIn,
    quarticOut,
    quarticInOut,
    quinticIn,
    quinticOut,
    quinticInOut,
    sinusoidalIn,
    sinusoidalOut,
    sinusoidalInOut,
    exponentialIn,
    exponentialOut,
    exponentialInOut,
    circularIn,
    circularOut,
    circularInOut,
    elasticIn,
    elasticOut,
    elasticInOut,
    backIn,
    backOut,
    backInOut,
    bounceIn,
    bounceOut,
    bounceInOut,
  };

  id id_;

  explicit byNameEasing(id i) : id_(i) {}

  static id parse(std::string_view name) {
    if (name == "linear") return id::linear;
    if (name == "def") return id::def;
    if (name == "stepped") return id::stepped;
    if (name == "quadraticIn") return id::quadraticIn;
    if (name == "quadraticOut") return id::quadraticOut;
    if (name == "quadraticInOut") return id::quadraticInOut;
    if (name == "cubicIn") return id::cubicIn;
    if (name == "cubicOut") return id::cubicOut;
    if (name == "cubicInOut") return id::cubicInOut;
    if (name == "quarticIn") return id::quarticIn;
    if (name == "quarticOut") return id::quarticOut;
    if (name == "quarticInOut") return id::quarticInOut;
    if (name == "quinticIn") return id::quinticIn;
    if (name == "quinticOut") return id::quinticOut;
    if (name == "quinticInOut") return id::quinticInOut;
    if (name == "sinusoidalIn") return id::sinusoidalIn;
    if (name == "sinusoidalOut") return id::sinusoidalOut;
    if (name == "sinusoidalInOut") return id::sinusoidalInOut;
    if (name == "exponentialIn") return id::exponentialIn;
    if (name == "exponentialOut") return id::exponentialOut;
    if (name == "exponentialInOut") return id::exponentialInOut;
    if (name == "circularIn") return id::circularIn;
    if (name == "circularOut") return id::circularOut;
    if (name == "circularInOut") return id::circularInOut;
    if (name == "elasticIn") return id::elasticIn;
    if (name == "elasticOut") return id::elasticOut;
    if (name == "elasticInOut") return id::elasticInOut;
    if (name == "backIn") return id::backIn;
    if (name == "backOut") return id::backOut;
    if (name == "backInOut") return id::backInOut;
    if (name == "bounceIn") return id::bounceIn;
    if (name == "bounceOut") return id::bounceOut;
    if (name == "bounceInOut") return id::bounceInOut;
    throw std::invalid_argument("unknown easing name: " + std::string(name));
  }

  friend byNameEasing byName(std::string_view name);

public:
  template <typename T>
  T operator()(const float position, T start, T end) const {
    switch (id_) {
      case id::linear: return linear(position, start, end);
      case id::def: return def(position, start, end);
      case id::stepped: return stepped(position, start, end);
      case id::quadraticIn: return quadraticIn(position, start, end);
      case id::quadraticOut: return quadraticOut(position, start, end);
      case id::quadraticInOut: return quadraticInOut(position, start, end);
      case id::cubicIn: return cubicIn(position, start, end);
      case id::cubicOut: return cubicOut(position, start, end);
      case id::cubicInOut: return cubicInOut(position, start, end);
      case id::quarticIn: return quarticIn(position, start, end);
      case id::quarticOut: return quarticOut(position, start, end);
      case id::quarticInOut: return quarticInOut(position, start, end);
      case id::quinticIn: return quinticIn(position, start, end);
      case id::quinticOut: return quinticOut(position, start, end);
      case id::quinticInOut: return quinticInOut(position, start, end);
      case id::sinusoidalIn: return sinusoidalIn(position, start, end);
      case id::sinusoidalOut: return sinusoidalOut(position, start, end);
      case id::sinusoidalInOut: return sinusoidalInOut(position, start, end);
      case id::exponentialIn: return exponentialIn(position, start, end);
      case id::exponentialOut: return exponentialOut(position, start, end);
      case id::exponentialInOut: return exponentialInOut(position, start, end);
      case id::circularIn: return circularIn(position, start, end);
      case id::circularOut: return circularOut(position, start, end);
      case id::circularInOut: return circularInOut(position, start, end);
      case id::elasticIn: return elasticIn(position, start, end);
      case id::elasticOut: return elasticOut(position, start, end);
      case id::elasticInOut: return elasticInOut(position, start, end);
      case id::backIn: return backIn(position, start, end);
      case id::backOut: return backOut(position, start, end);
      case id::backInOut: return backInOut(position, start, end);
      case id::bounceIn: return bounceIn(position, start, end);
      case id::bounceOut: return bounceOut(position, start, end);
      case id::bounceInOut: return bounceInOut(position, start, end);
    }
    throw std::invalid_argument("invalid easing id");
  }
};

/**
 * @brief Select a bundled easing by its identifier name.
 *
 * Names match the existing identifiers exactly (`linear`, `cubicInOut`, `bounceOut`,
 * `def`, `stepped`, …). Unknown names throw `std::invalid_argument` immediately.
 *
 * @code
 * auto e = tweeny::easing::byName("cubicInOut");
 * auto t = tweeny::from(0.f).to(1.f).via(e).during(60U).build();
 * // or: .via(tweeny::easing::byName("linear"))
 * @endcode
 *
 * @param name Exact easing identifier
 * @return Callable easing holding an internal id
 * @throws std::invalid_argument if @p name is not a known easing
 */
inline byNameEasing byName(std::string_view name) {
  return byNameEasing{byNameEasing::parse(name)};
}

} // namespace tweeny::easing

#endif // TWEENY_DETAIL_EASING_BY_NAME_H
