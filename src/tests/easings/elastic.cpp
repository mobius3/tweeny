#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::elasticIn matches Penner easeInElastic samples", "[easing][elastic]") {
  test_easing(tweeny::easing::elasticIn, easeInElastic);
}

TEST_CASE("easing::elasticOut matches Penner easeOutElastic samples", "[easing][elastic]") {
  test_easing(tweeny::easing::elasticOut, easeOutElastic);
}

TEST_CASE("easing::elasticInOut matches Penner easeInOutElastic samples", "[easing][elastic]") {
  test_easing(tweeny::easing::elasticInOut, easeInOutElastic);
}

TEST_CASE("tween via(elasticIn) matches Penner easeInElastic samples", "[easing][elastic][tween]") {
  test_tween_easing(tweeny::easing::elasticIn, easeInElastic);
}

TEST_CASE("tween via(elasticOut) matches Penner easeOutElastic samples", "[easing][elastic][tween]") {
  test_tween_easing(tweeny::easing::elasticOut, easeOutElastic);
}

TEST_CASE("tween via(elasticInOut) matches Penner easeInOutElastic samples", "[easing][elastic][tween]") {
  test_tween_easing(tweeny::easing::elasticInOut, easeInOutElastic);
}
