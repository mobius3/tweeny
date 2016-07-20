/*
 This file is part of the Tweeny library.

 Copyright (c) 2016 Leonardo G. Lucena de Freitas
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

/* This example uses tweens to control the frames of a sprite */

#include "tweeny.h"
#include "sprite.h"
#include "engine.h"
#include "input.h"
#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

/* References to resources in resources.c */
extern const unsigned char zombie_0_png[];
extern const unsigned int zombie_0_png_len;
extern const unsigned char arrows_to_walk_png[];
extern const unsigned int arrows_to_walk_png_len;

/* Forward declaration of loop and yoyo functions */
bool loop(tweeny::tween<int> & t, int);
bool yoyo(tweeny::tween<int> & t, int);

/* Enumerations representing which stripe should be used in the zombie sprite */
enum {
    SPRITE_LEFT = 0,
    SPRITE_LEFTUP = 1,
    SPRITE_UP = 2,
    SPRITE_RIGHTUP = 3,
    SPRITE_RIGHT = 4,
    SPRITE_RIGHTDOWN = 5,
    SPRITE_DOWN = 6,
    SPRITE_LEFTDOWN = 7
};

struct walk {
    int rx = 0, ry = 0, direction = SPRITE_LEFT;
};

walk process();

struct state {
    ex::engine engine = ex::engine(800, 600);
    ex::sprite zombie = engine.sprite(zombie_0_png, zombie_0_png_len, 36, 8);
    ex::sprite text = engine.sprite(arrows_to_walk_png, arrows_to_walk_png_len, 1, 1);
    tweeny::tween<float> idle = tweeny::from(0.0f).to(3.0f).during(1000).onStep(yoyo);
    tweeny::tween<float> walking = tweeny::from(4.0f).to(11.0f).during(1000).onStep(loop);
    walk w;
    float x = 0, y = 0;
    float frame = 0.0f;
    void run() {
        engine.clear();
        if (ex::input::pressed()) {
            w = process();
            x += 0.6f * w.rx;
            y += 0.6f * w.ry;
            frame = walking.step(engine.dt);
        } else {
            frame = idle.step(engine.dt);
        }
        text.render(0, 0);
        zombie.render(roundf(frame), w.direction, x, y);
        engine.delay(16);
        engine.flip();
    }
    bool quit() { return engine.quit(); }
};

void iterate(state * s) { s->run(); }

int main(int argc, char ** argv) {
    state s;
#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg((em_arg_callback_func)iterate, &s, 0, 1);
#else
    while (!s.quit()) iterate(&s);
#endif

}

walk process() {
    walk w;
    w.direction = SPRITE_LEFT;
    if (ex::input::up()) { w.direction = SPRITE_UP; w.ry = -1; }
    if (ex::input::down()) { w.direction = SPRITE_DOWN; w.ry = 1; }
    if (ex::input::left()) { w.direction = SPRITE_LEFT; w.rx = -1; }
    if (ex::input::right()) { w.direction = SPRITE_RIGHT; w.rx = 1; }
    if (ex::input::up() && ex::input::right()) w.direction = SPRITE_RIGHTUP;
    if (ex::input::right() && ex::input::down()) w.direction = SPRITE_RIGHTDOWN;
    if (ex::input::down() && ex::input::left()) w.direction = SPRITE_LEFTDOWN;
    if (ex::input::up() && ex::input::left()) w.direction = SPRITE_LEFTUP;
    return w;
}

/* yoyo's a tween */
bool yoyo(tweeny::tween<int> & t, int) {
    if (t.progress() >= 1.0f) t.backward();
    if (t.progress() <= 0.0f) t.forward();
    return false;
}

/* loop a tween */
bool loop(tweeny::tween<int> & t, int) {
    if (t.progress() >= 1.0f) t.seek(0);
    return false;
}

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


