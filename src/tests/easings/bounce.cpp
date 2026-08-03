#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::bounceIn matches Penner easeInBounce samples", "[easing][bounce]") {
  test_easing(tweeny::easing::bounceIn, easeInBounce);
}

TEST_CASE("easing::bounceOut matches Penner easeOutBounce samples", "[easing][bounce]") {
  test_easing(tweeny::easing::bounceOut, easeOutBounce);
}

TEST_CASE("easing::bounceInOut matches Penner easeInOutBounce samples", "[easing][bounce]") {
  test_easing(tweeny::easing::bounceInOut, easeInOutBounce);
}

TEST_CASE("tween via(bounceIn) matches Penner easeInBounce samples", "[easing][bounce][tween]") {
  test_tween_easing(tweeny::easing::bounceIn, easeInBounce);
}

TEST_CASE("tween via(bounceOut) matches Penner easeOutBounce samples", "[easing][bounce][tween]") {
  test_tween_easing(tweeny::easing::bounceOut, easeOutBounce);
}

TEST_CASE("tween via(bounceInOut) matches Penner easeInOutBounce samples", "[easing][bounce][tween]") {
  test_tween_easing(tweeny::easing::bounceInOut, easeInOutBounce);
}
