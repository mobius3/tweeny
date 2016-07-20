//
// Created by leo on 12/07/16.
//

#include "input.h"
#include "SDL.h"

namespace ex {
    bool keydown(int scancode) {
        static int numkeys = 0;
        static const uint8_t * state = SDL_GetKeyboardState(&numkeys);
        return state[scancode] != 0;
    }

    bool input::pressed() {
        return left() || right() || up() || down();
    }

    bool input::left() {
        return ex::keydown(SDL_SCANCODE_LEFT);
    }
    bool input::right() {
        return ex::keydown(SDL_SCANCODE_RIGHT);
    }
    bool input::up() {
        return ex::keydown(SDL_SCANCODE_UP);
    }
    bool input::down() {
        return ex::keydown(SDL_SCANCODE_DOWN);
    }
    bool input::space() {
        return ex::keydown(SDL_SCANCODE_SPACE);
    }
}







