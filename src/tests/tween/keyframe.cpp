#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

#include <vector>

TEST_CASE("keyframe() - starts at 0", "[tween][keyframe]") {
  auto t = tweeny::from(0)
             .to(50).during(30U)
             .to(100).during(30U)
             .build();

  REQUIRE(t.keyframe() == 0);
}

TEST_CASE("keyframe() - follows step forward and backward", "[tween][keyframe]") {
  auto t = tweeny::from(0)
             .to(50).during(30U)
             .to(100).during(30U)
             .build();

  t.step(29);
  REQUIRE(t.keyframe() == 0);

  t.step(1);
  REQUIRE(t.keyframe() == 1);

  t.step(15);
  REQUIRE(t.keyframe() == 1);

  t.step(-16);
  REQUIRE(t.keyframe() == 0);
}

TEST_CASE("keyframe() - is the last keyframe at the end", "[tween][keyframe]") {
  auto t = tweeny::from(0)
             .to(50).during(30U)
             .to(100).during(30U)
             .build();

  t.step(60);
  REQUIRE(t.keyframe() == 2);

  t.step(100);
  REQUIRE(t.keyframe() == 2);
}

TEST_CASE("keyframe() - follows seek", "[tween][keyframe][seek]") {
  auto t = tweeny::from(0)
             .to(50).during(30U)
             .to(100).during(30U)
             .build();

  t.seek(45U);
  REQUIRE(t.keyframe() == 1);

  t.seek(10U);
  REQUIRE(t.keyframe() == 0);
}

TEST_CASE("keyframe() - matches jump target", "[tween][keyframe][jump]") {
  auto t = tweeny::from(0)
             .to(50).during(30U)
             .to(100).during(30U)
             .build();

  for (std::size_t k = 0; k < 3; ++k) {
    t.jump(k);
    REQUIRE(t.keyframe() == k);
  }
}

TEST_CASE("keyframe() - is up to date inside step callbacks", "[tween][keyframe][events]") {
  auto t = tweeny::from(0)
             .to(50).during(10U)
             .to(100).during(40U)
             .build();

  std::vector<std::size_t> seen;
  t.on(tweeny::event::step, [&seen](auto & tween) {
    seen.push_back(tween.keyframe());
    return tweeny::event::response::ok;
  });

  t.step(5);
  t.step(5);
  t.step(20);
  t.step(-25);

  REQUIRE(seen == std::vector<std::size_t>{0, 1, 1, 0});
}
