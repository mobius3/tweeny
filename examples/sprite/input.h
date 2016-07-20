//
// Created by leo on 12/07/16.
//

#ifndef SPRITE_INPUT_H
#define SPRITE_INPUT_H

namespace ex {
    struct input {
        static bool pressed();
        static bool left();
        static bool right();
        static bool up();
        static bool down();
        static bool space();
    };
}

#endif //SPRITE_INPUT_H
