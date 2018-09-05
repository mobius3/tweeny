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

#ifndef TWEENY_SDL2_ENGINE_H
#define TWEENY_SDL2_ENGINE_H

#include "sprite.h"
#include "color.h"
#include "rect.h"
#include "cursor.h"

#include <vector>

struct SDL_Window;
struct SDL_Renderer;

namespace tweeny {
  namespace extras {
    namespace sdl2 {
      struct engine {
        SDL_Renderer * renderer = nullptr;
        SDL_Window * window = nullptr;
        int w = 0, h = 0;
        uint32_t start = 0, dt = 0;

        sdl2::color clearcolor;
        bool quitRequested = false;
        std::vector<sdl2::cursor> cursors;

        engine(int w, int h);
        ~engine();

        tweeny::extras::sdl2::sprite sprite(const unsigned char data[], unsigned int len, int framesx = 1, int framesy = 1);
        tweeny::extras::sdl2::sprite sprite(const char file[], int framesx = 1, int framesy = 1);

        tweeny::extras::sdl2::rect rect(float x, float y, float w, float h, const sdl2::color & fill = sdl2::color::black, sdl2::color & background = sdl2::color::black);

        void clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void clear(uint8_t r, uint8_t g, uint8_t b) { clear(r, g, b, clearcolor.a); }
        void clear(sdl2::color color) { clear(color.r, color.g, color.b, color.a); }
        void clear();
        void flip();
        bool quit();
        void delay(uint32_t ms);
        const sdl2::cursor & cursor(uint8_t index = 0);
      };
    }
  }
}
#endif //TWEENY_SDL2_ENGINE_H
