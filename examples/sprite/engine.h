#ifndef SPRITE_STATE_H
#define SPRITE_STATE_H

#include "sprite.h"

struct SDL_Window;
struct SDL_Renderer;

namespace ex {
    struct engine {
        SDL_Renderer * renderer = nullptr;
        SDL_Window * window = nullptr;
        int w = 0, h = 0;
        uint32_t start = 0, dt = 0;

        struct {
            uint8_t r, g, b, a;
        } clearcolor = { 200, 200, 255, 0 };

        engine(int w, int h);
        ~engine();
        ex::sprite sprite(const unsigned char data[], unsigned int len, int framesx = 1, int framesy = 1);
        ex::sprite sprite(const char file[], int framesx = 1, int framesy = 1);
        void clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void clear(uint8_t r, uint8_t g, uint8_t b) { clear(r, g, b, clearcolor.a); }
        void clear();
        void flip();
        bool quit();
        void delay(uint32_t ms);
    };
}
#endif //SPRITE_STATE_H
