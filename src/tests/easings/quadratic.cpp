#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::quadraticIn matches Penner easeInQuad samples", "[easing][quadratic]") {
  test_easing(tweeny::easing::quadraticIn, easeInQuad);
}

TEST_CASE("easing::quadraticOut matches Penner easeOutQuad samples", "[easing][quadratic]") {
  test_easing(tweeny::easing::quadraticOut, easeOutQuad);
}

TEST_CASE("easing::quadraticInOut matches Penner easeInOutQuad samples", "[easing][quadratic]") {
  test_easing(tweeny::easing::quadraticInOut, easeInOutQuad);
}

TEST_CASE("tween via(quadraticIn) matches Penner easeInQuad samples", "[easing][quadratic][tween]") {
  test_tween_easing(tweeny::easing::quadraticIn, easeInQuad);
}

TEST_CASE("tween via(quadraticOut) matches Penner easeOutQuad samples", "[easing][quadratic][tween]") {
  test_tween_easing(tweeny::easing::quadraticOut, easeOutQuad);
}

TEST_CASE("tween via(quadraticInOut) matches Penner easeInOutQuad samples", "[easing][quadratic][tween]") {
  test_tween_easing(tweeny::easing::quadraticInOut, easeInOutQuad);
}
