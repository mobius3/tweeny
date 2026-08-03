#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::sinusoidalIn matches Penner easeInSine samples", "[easing][sinusoidal]") {
  test_easing(tweeny::easing::sinusoidalIn, easeInSine);
}

TEST_CASE("easing::sinusoidalOut matches Penner easeOutSine samples", "[easing][sinusoidal]") {
  test_easing(tweeny::easing::sinusoidalOut, easeOutSine);
}

TEST_CASE("easing::sinusoidalInOut matches Penner easeInOutSine samples", "[easing][sinusoidal]") {
  test_easing(tweeny::easing::sinusoidalInOut, easeInOutSine);
}

TEST_CASE("tween via(sinusoidalIn) matches Penner easeInSine samples", "[easing][sinusoidal][tween]") {
  test_tween_easing(tweeny::easing::sinusoidalIn, easeInSine);
}

TEST_CASE("tween via(sinusoidalOut) matches Penner easeOutSine samples", "[easing][sinusoidal][tween]") {
  test_tween_easing(tweeny::easing::sinusoidalOut, easeOutSine);
}

TEST_CASE("tween via(sinusoidalInOut) matches Penner easeInOutSine samples", "[easing][sinusoidal][tween]") {
  test_tween_easing(tweeny::easing::sinusoidalInOut, easeInOutSine);
}
