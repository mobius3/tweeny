#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::exponentialIn matches Penner easeInExpo samples", "[easing][exponential]") {
  test_easing(tweeny::easing::exponentialIn, easeInExpo);
}

TEST_CASE("easing::exponentialOut matches Penner easeOutExpo samples", "[easing][exponential]") {
  test_easing(tweeny::easing::exponentialOut, easeOutExpo);
}

TEST_CASE("easing::exponentialInOut matches Penner easeInOutExpo samples", "[easing][exponential]") {
  test_easing(tweeny::easing::exponentialInOut, easeInOutExpo);
}

TEST_CASE("tween via(exponentialIn) matches Penner easeInExpo samples", "[easing][exponential][tween]") {
  test_tween_easing(tweeny::easing::exponentialIn, easeInExpo);
}

TEST_CASE("tween via(exponentialOut) matches Penner easeOutExpo samples", "[easing][exponential][tween]") {
  test_tween_easing(tweeny::easing::exponentialOut, easeOutExpo);
}

TEST_CASE("tween via(exponentialInOut) matches Penner easeInOutExpo samples", "[easing][exponential][tween]") {
  test_tween_easing(tweeny::easing::exponentialInOut, easeInOutExpo);
}
