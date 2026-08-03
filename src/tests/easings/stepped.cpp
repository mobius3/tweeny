#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>
#include <tweeny/tweeny.h>

TEST_CASE("easing::stepped always returns start", "[easing][stepped]") {
  for (int i = 0; i <= 100; ++i) {
    const float position = static_cast<float>(i) / 100.f;
    REQUIRE(tweeny::easing::stepped.run(position, 0.f, 1.f) == Catch::Approx(0.f).margin(1e-6f));
    REQUIRE(tweeny::easing::stepped.run(position, 10, 20) == 10);
  }
}

TEST_CASE("tween via(stepped) holds start until the end keyframe", "[easing][stepped][tween]") {
  auto tween = tweeny::from(0.f).to(1.f).via(tweeny::easing::stepped).during(100U).build();

  for (uint32_t t = 0; t < 100U; ++t) {
    REQUIRE(tween.peek(t) == Catch::Approx(0.f).margin(1e-6f));
  }

  // At the final keyframe position, render returns the keyframe value (not via easing).
  REQUIRE(tween.peek(100U) == Catch::Approx(1.f).margin(1e-6f));
}

TEST_CASE("tween via(stepped) snaps at each keyframe with no in-between easing", "[easing][stepped][tween]") {
  auto tween = tweeny::from(0)
    .to(10).via(tweeny::easing::stepped).during(100U)
    .to(20).via(tweeny::easing::stepped).during(100U)
    .to(30).via(tweeny::easing::stepped).during(100U)
    .build();

  for (uint32_t t = 0; t < 100U; ++t) {
    REQUIRE(tween.peek(t) == 0);
  }
  for (uint32_t t = 100; t < 200U; ++t) {
    REQUIRE(tween.peek(t) == 10);
  }
  for (uint32_t t = 200; t < 300U; ++t) {
    REQUIRE(tween.peek(t) == 20);
  }

  REQUIRE(tween.peek(100U) == 10);
  REQUIRE(tween.peek(200U) == 20);
  REQUIRE(tween.peek(300U) == 30);
}
