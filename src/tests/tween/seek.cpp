#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("seek() - jumps to target frame", "[tween][seek]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  auto val = t.seek(50U);
  REQUIRE(val == 50);
  REQUIRE(t.peek() == 50);
}

TEST_CASE("seek() - can jump forward and backward", "[tween][seek]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  t.seek(75U);
  REQUIRE(t.peek() == 75);

  t.seek(25U);
  REQUIRE(t.peek() == 25);

  t.seek(100U);
  REQUIRE(t.peek() == 100);

  t.seek(0U);
  REQUIRE(t.peek() == 0);
}

TEST_CASE("seek() - clamped to valid range", "[tween][seek]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  t.seek(200U);  // Beyond end
  REQUIRE(t.peek() == 100);
}

TEST_CASE("seek() - multi-point tween", "[tween][seek]") {
  auto t = tweeny::from(0)
             .to(50).during(50U)
             .to(100).during(50U)
             .build();

  t.seek(25U);
  REQUIRE(t.peek() == 25);

  t.seek(50U);
  REQUIRE(t.peek() == 50);

  t.seek(75U);
  REQUIRE(t.peek() == 75);
}

TEST_CASE("seek() - multi-value tween", "[tween][seek]") {
  auto t = tweeny::from(0, 100.0f)
             .to(100, 0.0f)
             .during(100U)
             .build();

  auto result = t.seek(50U);
  REQUIRE(std::get<0>(result) == 50);
  REQUIRE(std::get<1>(result) == 50.0f);
}

TEST_CASE("seek() - returns interpolated value", "[tween][seek]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  for (uint32_t i = 0; i <= 100; i += 10) {
    auto val = t.seek(i);
    REQUIRE(val == static_cast<int>(i));
  }
}
