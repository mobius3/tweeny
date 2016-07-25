#include "tweeny.h"

int main(int argc, char ** argv) {
    auto tween = tweeny::from(0, 0.0f).to(2, 2.0f).during(100).onStep([](int i, float f) { printf("i=%d f=%f\n", i, f); return false; });
    while(tween.progress() < 1.0f) tween.step(1);
    return 0;
}
