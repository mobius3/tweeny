#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("peek() - returns current value without mutation", "[peek]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  REQUIRE(t.peek() == 0);
  t.step(50);
  REQUIRE(t.peek() == 50);
}

TEST_CASE("peek(frame) - queries value at arbitrary frame without mutation", "[peek]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  // Should not change current position
  REQUIRE(t.peek(50U) == 50);
  REQUIRE(t.peek() == 0);  // Still at start
  REQUIRE(t.progress() == Catch::Approx(0.0f));
}

TEST_CASE("peek(frame) - multi-value tween", "[peek]") {
  auto t = tweeny::from(0, 0.0f)
             .to(100, 100.0f)
             .during(100U)
             .build();

  auto result = t.peek(50U);
  REQUIRE(std::get<0>(result) == 50);
  REQUIRE(std::get<1>(result) == Catch::Approx(50.0f));
}

TEST_CASE("progress() - returns 0.0 at start", "[progress]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  REQUIRE(t.progress() == Catch::Approx(0.0f));
}

TEST_CASE("progress() - returns 1.0 at end", "[progress]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  t.seek(100U);
  REQUIRE(t.progress() == Catch::Approx(1.0f));
}

TEST_CASE("progress() - returns 0.5 at midpoint", "[progress]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  t.step(50);
  REQUIRE(t.progress() == Catch::Approx(0.5f));
}

TEST_CASE("progress() - multi-point tween", "[progress]") {
  auto t = tweeny::from(0)
             .to(50).during(50U)
             .to(100).during(50U)
             .build();

  REQUIRE(t.progress() == Catch::Approx(0.0f));

  t.seek(25U);
  REQUIRE(t.progress() == Catch::Approx(0.25f));

  t.seek(50U);
  REQUIRE(t.progress() == Catch::Approx(0.5f));

  t.seek(75U);
  REQUIRE(t.progress() == Catch::Approx(0.75f));

  t.seek(100U);
  REQUIRE(t.progress() == Catch::Approx(1.0f));
}

TEST_CASE("progress() - handles empty keyframes", "[progress]") {
  // Edge case: this shouldn't happen in practice but let's be defensive
  auto t = tweeny::from(0)
             .to(100)
             .during(0U)
             .build();

  REQUIRE(t.progress() == Catch::Approx(1.0f));
}

TEST_CASE("peek() and progress() - consistent after stepping", "[peek][progress]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  for (int i = 0; i <= 100; i += 10) {
    t.seek(static_cast<uint32_t>(i));
    REQUIRE(t.peek() == i);
    REQUIRE(t.progress() == Catch::Approx(static_cast<float>(i) / 100.0f));
  }
}
