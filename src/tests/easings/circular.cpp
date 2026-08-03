#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::circularIn matches Penner easeInCirc samples", "[easing][circular]") {
  test_easing(tweeny::easing::circularIn, easeInCirc);
}

TEST_CASE("easing::circularOut matches Penner easeOutCirc samples", "[easing][circular]") {
  test_easing(tweeny::easing::circularOut, easeOutCirc);
}

TEST_CASE("easing::circularInOut matches Penner easeInOutCirc samples", "[easing][circular]") {
  test_easing(tweeny::easing::circularInOut, easeInOutCirc);
}
