#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("step() - advances by positive delta", "[tween][step]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  auto val = t.step(10);
  REQUIRE(val == 10);
  REQUIRE(t.peek() == 10);

  val = t.step(20);
  REQUIRE(val == 30);
  REQUIRE(t.peek() == 30);
}

TEST_CASE("step() - rewinds by negative delta", "[tween][step]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  t.step(50);
  REQUIRE(t.peek() == 50);

  t.step(-20);
  REQUIRE(t.peek() == 30);

  t.step(-10);
  REQUIRE(t.peek() == 20);
}

TEST_CASE("step() - clamped at start", "[tween][step]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  t.step(10);
  t.step(-100);  // Try to go negative
  REQUIRE(t.peek() == 0);
}

TEST_CASE("step() - clamped at end", "[tween][step]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  t.step(200);  // Overshoot
  REQUIRE(t.peek() == 100);
}

TEST_CASE("step() - multi-value tween", "[tween][step]") {
  auto t = tweeny::from(0, 0.0f)
             .to(100, 50.0f)
             .during(100U)
             .build();

  auto result = t.step(50);
  REQUIRE(std::get<0>(result) == 50);
  REQUIRE(std::get<1>(result) == 25.0f);
}

TEST_CASE("step() - returns interpolated value", "[tween][step]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  for (int i = 1; i <= 10; i++) {
    auto val = t.step(10);
    REQUIRE(val == i * 10);
  }
}
