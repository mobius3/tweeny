#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::quarticIn matches Penner easeInQuart samples", "[easing][quartic]") {
  test_easing(tweeny::easing::quarticIn, easeInQuart);
}

TEST_CASE("easing::quarticOut matches Penner easeOutQuart samples", "[easing][quartic]") {
  test_easing(tweeny::easing::quarticOut, easeOutQuart);
}

TEST_CASE("easing::quarticInOut matches Penner easeInOutQuart samples", "[easing][quartic]") {
  test_easing(tweeny::easing::quarticInOut, easeInOutQuart);
}
