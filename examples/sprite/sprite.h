/*
 This file is part of the Tweeny library.

 Copyright (c) 2016-2017 Leonardo G. Lucena de Freitas
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

#ifndef SPRITE_SPRITE_H
#define SPRITE_SPRITE_H

struct SDL_Texture;
struct SDL_Renderer;

namespace ex {
    class sprite {
        public:
            sprite(sprite && other);
            sprite(const sprite & other);
            sprite(SDL_Renderer * renderer, const char file[], int framesx, int framesy);
            sprite(SDL_Renderer * renderer, const unsigned char data[], unsigned int len, int framesx, int framesy);
            ~sprite();
            void render(int framex, int framey, int x, int y, double angle = 0.0f);
            void render(int x, int y, double angle = 0.0f);

        private:
            void make(unsigned char * pixels, int bpp);
            SDL_Texture * texture;
            SDL_Renderer * renderer;
            int w, h;
            int framesx, framesy;
    };
}

#endif //SPRITE_SPRITE_H
