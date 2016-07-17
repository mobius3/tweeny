#include "tweeny.h"
#include "sprite.h"
#include "engine.h"
#include "input.h"
#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

extern const unsigned char zombie_0_png[];
extern const unsigned int zombie_0_png_len;
extern const unsigned char arrows_to_walk_png[];
extern const unsigned int arrows_to_walk_png_len;

bool loop(tweeny::tween<float> & t, float);
bool yoyo(tweeny::tween<float> & t, float);

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

bool yoyo(tweeny::tween<float> & t, float) {
    if (t.progress() >= 1.0f) t.backward();
    if (t.progress() <= 0.0f) t.forward();
    return false;
}

bool loop(tweeny::tween<float> & t, float) {
    if (t.progress() >= 1.0f) t.seek(0);
    return false;
}

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


