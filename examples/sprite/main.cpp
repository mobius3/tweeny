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

/* The state represents the "game state": it contains sprites, tweens and other
 * variables. It also has the run() function that is called in each frame */
struct state {
    ex::engine engine = ex::engine(800, 600); /* creates the window and initializes SDL */
    ex::sprite text = engine.sprite(arrows_to_walk_png, arrows_to_walk_png_len, 1, 1); /* help text */
    struct zombie {
        float x = 0;
        float y = 0;
        int direction = SPRITE_RIGHT;
        bool attack = false;
        int frame = 0;
        ex::sprite sprite;
        tweeny::tween<int> idle = tweeny::from(0).to(3).during(1000).onStep(yoyo); /* idle animation */
        tweeny::tween<int> walking = tweeny::from(4).to(11).during(1000).onStep(loop); /* walking animation */
        tweeny::tween<int> attacking = tweeny::from(12).to(15).during(300).to(14).during(300).onStep([this](tweeny::tween<int> & t, int) {
            /* attacking animation. when ended, stops the attack */
            if (t.progress() >= 1.0f) { attack = false; }
            return false;
        });
        zombie(ex::engine & engine) : sprite(engine.sprite(zombie_0_png, zombie_0_png_len, 36, 8)) { }
    } z = zombie(engine);

    /* Run a frame */
    void run() {
        engine.clear(93, 77, 157); /* clear the screen */
        process(); /* process all input */

        /* decides which animation should be running */
        if (z.attack) z.frame = z.attacking.step(engine.dt);
        else {
            if (ex::input::pressed()) z.frame = z.walking.step(engine.dt);
            else z.frame = z.idle.step(engine.dt);
        }

        text.render(10, 10); /* render help text */
        z.sprite.render(z.frame, z.direction, z.x, z.y); /* render zombie sprite */
        engine.delay(16);
        engine.flip();
    }

    /* process the input state and sets attacking state */
    void process() {
        if (ex::input::up()) { z.direction = SPRITE_UP; if (!z.attack) z.y -= 1.0f; }
        if (ex::input::down()) { z.direction = SPRITE_DOWN; if (!z.attack) z.y += 1.0f; }
        if (ex::input::left()) { z.direction = SPRITE_LEFT; if (!z.attack) z.x -= 1.0f; }
        if (ex::input::right()) { z.direction = SPRITE_RIGHT; if (!z.attack) z.x += 1.0f; }
        if (ex::input::up() && ex::input::right()) z.direction = SPRITE_RIGHTUP;
        if (ex::input::right() && ex::input::down()) z.direction = SPRITE_RIGHTDOWN;
        if (ex::input::down() && ex::input::left()) z.direction = SPRITE_LEFTDOWN;
        if (ex::input::up() && ex::input::left()) z.direction = SPRITE_LEFTUP;
        if (ex::input::space()) {
            z.attacking.seek(0);
            z.attack = true;
        }
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


