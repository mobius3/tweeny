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

/*
 * This is the easings example. It will print all known easings to the console. For each easing, it waits for you
 * to hit the return key to present the next.
 */

#include "tweeny.h"
#include <cstdio>

using tweeny::easing;
using std::printf;
using std::getchar;

/* Callback for the tweening */
bool print(tweeny::tween<int> &, int p);

/* Runs the tween with the designated easing */
template<typename EasingT> void test(tweeny::tween<int> & tween, EasingT easing);

/* Nacro to help call test() with each type of easing */
#define EASING_TEST(tween, easing) \
    getchar(); \
    printf("%s\n", #easing " In/Out/InOut"); \
    test(tween, easing ## In); \
    test(tween, easing ## Out); \
    test(tween, easing ## InOut)


int main() {
    /* Creates the tweening. By default tweenings use a linear easing */
    auto t = tweeny::from(0).to(100).during(100).onStep(print);

    /* Start with linear */
    printf("tweeny::easing::linear\n");
    test(t, easing::linear);

    /* Test all the other easings */
    EASING_TEST(t, tweeny::easing::quadratic);
    EASING_TEST(t, tweeny::easing::cubic);
    EASING_TEST(t, tweeny::easing::quartic);
    EASING_TEST(t, tweeny::easing::quintic);
    EASING_TEST(t, tweeny::easing::sinusoidal);
    EASING_TEST(t, tweeny::easing::exponential);
    EASING_TEST(t, tweeny::easing::circular);
    EASING_TEST(t, tweeny::easing::bounce);
    EASING_TEST(t, tweeny::easing::elastic);
    EASING_TEST(t, tweeny::easing::back);
    return 0;
}

/* Set the easing, seek to beginning, loop until 100 */
template<typename EasingT> void test(tweeny::tween<int> & tween, EasingT easing) {
    tween.via(0, easing);
    tween.seek(0);
    for (int i = 0; i <= 100; i++) tween.step(0.01f);
}

/* Prints a line, showing the tween value and a dot corresponding to that value */
bool print(tweeny::tween<int> &, int p) {
    printf("%+.3d |", p); // 3 digits with sign
    for (int i = 0; i <= 100; i++) printf("%c", i == p ? '.' : ' '); // prints the line
    printf("%c\n", p == 100 ? ';' : '|');
    return false;
}
