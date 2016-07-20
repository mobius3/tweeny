//
// Created by leo on 10/07/16.
//

#include "SDL.h"
#include "engine.h"
#include "sprite.h"

namespace ex {
    ex::sprite engine::sprite(const unsigned char * data, unsigned int len, int framesx, int framesy) {
        return ex::sprite{renderer, data, len, framesx, framesy};
    }

    ex::sprite engine::sprite(const char * file, int framesx, int framesy) {
        return ex::sprite{renderer, file, framesx, framesy};
    }

    engine::engine(int w, int h) {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }

    engine::~engine() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }

    void engine::clear() {
        clear(clearcolor.r, clearcolor.g, clearcolor.b, clearcolor.a);
    }

    void engine::clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        start = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderClear(renderer);
    }

    void engine::flip() {
        SDL_RenderPresent(renderer);
        dt = SDL_GetTicks() - start;
    }

    bool engine::quit() {
        return SDL_QuitRequested();
    }

    void engine::delay(uint32_t ms) {
        SDL_Delay(ms);
    }


}




