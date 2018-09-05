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

#include <iostream>
#include "tweeny.h"
#include "extras/sdl2/sprite.h"
#include "extras/sdl2/engine.h"
#include "extras/sdl2/input.h"
#include "extras/sdl2/rect.h"

using namespace tweeny::extras;

int main(int argc, char ** argv) {
  const auto & a = sdl2::color::yellow, & b = sdl2::color::blue;
  sdl2::engine engine(800, 600);
  sdl2::rect r = engine.rect(0, 0, 400, 400, a);
  auto t = tweeny::from(a).to(b).during(400).via(tweeny::easing::sinusoidalOut);
  while (!engine.quit()) {
    engine.clear(100, 100, 200);
    r.fill(t.step(16));
    r.render();
    engine.delay(16);
    engine.flip();
  }
}


