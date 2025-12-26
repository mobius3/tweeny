#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("jump() - jumps to keyframe by index", "[tween][jump]") {
  auto t = tweeny::from(0)
             .to(50).during(50U)
             .to(100).during(50U)
             .build();

  auto val = t.jump(0);
  REQUIRE(val == 0);

  val = t.jump(1);
  REQUIRE(val == 50);

  val = t.jump(2);
  REQUIRE(val == 100);
}

TEST_CASE("jump() - clamped to valid keyframe range", "[tween][jump]") {
  auto t = tweeny::from(0)
             .to(50).during(50U)
             .to(100).during(50U)
             .build();

  t.jump(10);  // Beyond last keyframe
  REQUIRE(t.peek() == 100);
}

TEST_CASE("jump() - works with two-point tween", "[tween][jump]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  t.jump(0);
  REQUIRE(t.peek() == 0);

  t.jump(1);
  REQUIRE(t.peek() == 100);
}

TEST_CASE("jump() - multi-value tween", "[tween][jump]") {
  auto t = tweeny::from(0, 0.0f)
             .to(50, 25.0f).during(50U)
             .to(100, 100.0f).during(50U)
             .build();

  auto result = t.jump(1);
  REQUIRE(std::get<0>(result) == 50);
  REQUIRE(std::get<1>(result) == 25.0f);

  result = t.jump(2);
  REQUIRE(std::get<0>(result) == 100);
  REQUIRE(std::get<1>(result) == 100.0f);
}

TEST_CASE("jump() - can jump backward", "[tween][jump]") {
  auto t = tweeny::from(0)
             .to(50).during(50U)
             .to(100).during(50U)
             .build();

  t.jump(2);
  REQUIRE(t.peek() == 100);

  t.jump(0);
  REQUIRE(t.peek() == 0);

  t.jump(1);
  REQUIRE(t.peek() == 50);
}
