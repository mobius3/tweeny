#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::quinticIn matches Penner easeInQuint samples", "[easing][quintic]") {
  test_easing(tweeny::easing::quinticIn, easeInQuint);
}

TEST_CASE("easing::quinticOut matches Penner easeOutQuint samples", "[easing][quintic]") {
  test_easing(tweeny::easing::quinticOut, easeOutQuint);
}

TEST_CASE("easing::quinticInOut matches Penner easeInOutQuint samples", "[easing][quintic]") {
  test_easing(tweeny::easing::quinticInOut, easeInOutQuint);
}

TEST_CASE("tween via(quinticIn) matches Penner easeInQuint samples", "[easing][quintic][tween]") {
  test_tween_easing(tweeny::easing::quinticIn, easeInQuint);
}

TEST_CASE("tween via(quinticOut) matches Penner easeOutQuint samples", "[easing][quintic][tween]") {
  test_tween_easing(tweeny::easing::quinticOut, easeOutQuint);
}

TEST_CASE("tween via(quinticInOut) matches Penner easeInOutQuint samples", "[easing][quintic][tween]") {
  test_tween_easing(tweeny::easing::quinticInOut, easeInOutQuint);
}
