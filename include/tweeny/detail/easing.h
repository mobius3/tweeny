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

/**
 * @file easing.h
 * The purpose of this file is to list all bundled easings. Each easing is defined
 * in its own header under include/tweeny/detail/easing/. Users may include individual
 * easing headers or this header to get all easings.
 */

#ifndef TWEENY_DETAIL_EASING_H
#define TWEENY_DETAIL_EASING_H

#include "tweeny/detail/easing/stepped.h"
#include "tweeny/detail/easing/def.h"
#include "tweeny/detail/easing/linear.h"
#include "tweeny/detail/easing/quadratic.h"
#include "tweeny/detail/easing/cubic.h"
#include "tweeny/detail/easing/quartic.h"
#include "tweeny/detail/easing/quintic.h"
#include "tweeny/detail/easing/sinusoidal.h"
#include "tweeny/detail/easing/exponential.h"
#include "tweeny/detail/easing/circular.h"
#include "tweeny/detail/easing/bounce.h"
#include "tweeny/detail/easing/elastic.h"
#include "tweeny/detail/easing/back.h"

#endif //TWEENY_DETAIL_EASING_H
