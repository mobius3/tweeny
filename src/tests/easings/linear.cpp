#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::linear matches Penner reference samples", "[easing][linear]") {
  test_easing(tweeny::easing::linear, linear);
}
