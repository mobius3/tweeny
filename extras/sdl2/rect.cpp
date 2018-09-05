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

#include "rect.h"
#include "color.h"

#include "SDL.h"

struct colorguard {
  SDL_Color old;
  SDL_Renderer * renderer;
  colorguard(SDL_Renderer * renderer, const tweeny::extras::sdl2::color & color)
    : renderer(renderer)
  {
    SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.b, &old.a);
    SDL_SetRenderDrawColor(renderer, static_cast<unsigned char>(color.r),
                           static_cast<unsigned char>(color.g),
                           static_cast<unsigned char>(color.b),
                           static_cast<unsigned char>(color.a));
  }

  ~colorguard() {
    SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a);
  }
};

tweeny::extras::sdl2::rect::rect(tweeny::extras::sdl2::rect && other) noexcept
  : renderer(other.renderer)
  , fg(other.fg)
  , bg(other.bg)
  , x(other.x)
  , y(other.y)
  , w(other.w)
  , h(other.h)
{
  other.renderer = nullptr;
}

tweeny::extras::sdl2::rect::rect(SDL_Renderer * renderer,
                                 float x, float y, float w, float h,
                                 const tweeny::extras::sdl2::color & background,
                                 const tweeny::extras::sdl2::color & line)
  : renderer(renderer)
  , fg(line)
  , bg(background)
  , x(x)
  , y(y)
  , w(w)
  , h(h)
{

}

void tweeny::extras::sdl2::rect::fill(const tweeny::extras::sdl2::color & bg) {
  this->bg = bg;
}

void tweeny::extras::sdl2::rect::border(const tweeny::extras::sdl2::color & fg) {
  this->fg = fg;
}

void tweeny::extras::sdl2::rect::render() {
  int ww = 0, wh = 0;
  SDL_GetRendererOutputSize(renderer, &ww, &wh);
  SDL_Rect r = {
    static_cast<int>(x + (ww/2) - w/2),
    static_cast<int>(y + (wh/2) - h/2),
    static_cast<int>(w),
    static_cast<int>(h)
  };
  {
    colorguard guard(renderer, bg);
    SDL_RenderFillRect(renderer, &r);
  }
  {
    colorguard guard(renderer, fg);
    SDL_RenderDrawRect(renderer, &r);
  }
}

