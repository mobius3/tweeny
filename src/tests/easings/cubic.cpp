#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::cubicIn matches Penner easeInCubic samples", "[easing][cubic]") {
  test_easing(tweeny::easing::cubicIn, easeInCubic);
}

TEST_CASE("easing::cubicOut matches Penner easeOutCubic samples", "[easing][cubic]") {
  test_easing(tweeny::easing::cubicOut, easeOutCubic);
}

TEST_CASE("easing::cubicInOut matches Penner easeInOutCubic samples", "[easing][cubic]") {
  test_easing(tweeny::easing::cubicInOut, easeInOutCubic);
}
