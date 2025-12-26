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

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file easing.h
 * The purpose of this file is to list all bundled easings. Each easing is defined
 * in its own header under include/tweeny/detail/easing/. Users may include individual
 * easing headers or this header to get all easings.
 */

#ifndef TWEENY_EASING_H
#define TWEENY_EASING_H

#include "detail/easing/back.h"
#include "detail/easing/bounce.h"
#include "detail/easing/circular.h"
#include "detail/easing/cubic.h"
#include "detail/easing/def.h"
#include "detail/easing/elastic.h"
#include "detail/easing/exponential.h"
#include "detail/easing/linear.h"
#include "detail/easing/quadratic.h"
#include "detail/easing/quartic.h"
#include "detail/easing/quintic.h"
#include "detail/easing/sinusoidal.h"
#include "detail/easing/stepped.h"

namespace tweeny::easing {
 inline constexpr detail::backInEasing backIn{};
 inline constexpr detail::backOutEasing backOut{};
 inline constexpr detail::backInOutEasing backInOut{};
 inline constexpr detail::bounceInEasing bounceIn{};
 inline constexpr detail::bounceOutEasing bounceOut{};
 inline constexpr detail::bounceInOutEasing bounceInOut{};
 inline constexpr detail::circularInEasing circularIn{};
 inline constexpr detail::circularOutEasing circularOut{};
 inline constexpr detail::circularInOutEasing circularInOut{};
 inline constexpr detail::cubicInEasing cubicIn{};
 inline constexpr detail::cubicOutEasing cubicOut{};
 inline constexpr detail::cubicInOutEasing cubicInOut{};
 inline constexpr detail::defaultEasing def{};
 inline constexpr detail::elasticInEasing elasticIn{};
 inline constexpr detail::elasticOutEasing elasticOut{};
 inline constexpr detail::elasticInOutEasing elasticInOut{};
 inline constexpr detail::exponentialInEasing exponentialIn{};
 inline constexpr detail::exponentialOutEasing exponentialOut{};
 inline constexpr detail::exponentialInOutEasing exponentialInOut{};
 inline constexpr detail::linearEasing linear{};
 inline constexpr detail::quadraticInEasing quadraticIn{};
 inline constexpr detail::quadraticOutEasing quadraticOut{};
 inline constexpr detail::quadraticInOutEasing quadraticInOut{};
 inline constexpr detail::quarticInEasing quarticIn{};
 inline constexpr detail::quarticOutEasing quarticOut{};
 inline constexpr detail::quarticInOutEasing quarticInOut{};
 inline constexpr detail::quinticInEasing quinticIn{};
 inline constexpr detail::quinticOutEasing quinticOut{};
 inline constexpr detail::quinticInOutEasing quinticInOut{};
 inline constexpr detail::sinusoidalInEasing sinusoidalIn{};
 inline constexpr detail::sinusoidalOutEasing sinusoidalOut{};
 inline constexpr detail::sinusoidalInOutEasing sinusoidalInOut{};
 inline constexpr detail::steppedEasing stepped{};
}

#endif //TWEENY_EASING_H
