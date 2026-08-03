#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <tweeny/easing.h>
#include <tweeny/tweeny.h>

TEST_CASE("byName(cubicInOut) matches easing::cubicInOut", "[easing][byName]") {
  const auto named = tweeny::easing::byName("cubicInOut");
  for (float p : {0.f, 0.25f, 0.5f, 0.75f, 1.f}) {
    REQUIRE(named(p, 0.f, 1.f) == Catch::Approx(tweeny::easing::cubicInOut(p, 0.f, 1.f)));
  }
}

TEST_CASE("via(byName(linear)) matches via(linear) over 0..100", "[easing][byName][tween]") {
  auto named = tweeny::from(0.f).to(100.f).via(tweeny::easing::byName("linear")).during(100U).build();
  auto direct = tweeny::from(0.f).to(100.f).via(tweeny::easing::linear).during(100U).build();
  for (uint32_t frame = 0; frame <= 100U; ++frame) {
    REQUIRE(named.peek(frame) == Catch::Approx(direct.peek(frame)));
  }
}

TEST_CASE("byName throws on unknown name", "[easing][byName]") {
  REQUIRE_THROWS_AS(tweeny::easing::byName("notAnEasing"), std::invalid_argument);
  REQUIRE_THROWS_AS(tweeny::easing::byName("cubic-in-out"), std::invalid_argument);
  REQUIRE_THROWS_AS(tweeny::easing::byName(""), std::invalid_argument);
}

TEST_CASE("byName works with int values", "[easing][byName]") {
  const auto named = tweeny::easing::byName("linear");
  REQUIRE(named(0.f, 0, 100) == 0);
  REQUIRE(named(0.5f, 0, 100) == 50);
  REQUIRE(named(1.f, 0, 100) == 100);

  auto tween = tweeny::from(0).to(100).via(named).during(100U).build();
  REQUIRE(tween.peek(50U) == 50);
}
