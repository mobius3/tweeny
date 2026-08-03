#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>
#include <tweeny/tweeny.h>

#include "test-easing.h"

TEST_CASE("easing::def matches Penner linear samples", "[easing][def]") {
  test_easing(tweeny::easing::def, linear);
}

TEST_CASE("tween via(def) matches Penner linear samples", "[easing][def][tween]") {
  test_tween_easing(tweeny::easing::def, linear);
}

TEST_CASE("tween without via() uses def (linear) behavior", "[easing][def][tween]") {
  auto with_def = tweeny::from(0.f).to(1.f).via(tweeny::easing::def).during(100U).build();
  auto implicit = tweeny::from(0.f).to(1.f).during(100U).build();
  for (std::size_t t = 0; t < sample_count; ++t) {
    const auto frame = static_cast<uint32_t>(t);
    REQUIRE(implicit.peek(frame) == Catch::Approx(with_def.peek(frame)).margin(1e-6f));
  }
}
