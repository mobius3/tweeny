#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("peek() - returns current value without mutation", "[tween][peek]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  REQUIRE(t.peek() == 0);
  t.step(50);
  REQUIRE(t.peek() == 50);
}

TEST_CASE("peek(frame) - queries value at arbitrary frame without mutation", "[tween][peek]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  // Should not change current position
  REQUIRE(t.peek(50U) == 50);
  REQUIRE(t.peek() == 0);  // Still at start
  REQUIRE(t.progress() == Catch::Approx(0.0f));
}

TEST_CASE("peek(frame) - multi-value tween", "[tween][peek]") {
  auto t = tweeny::from(0, 0.0f)
             .to(100, 100.0f)
             .during(100U)
             .build();

  auto result = t.peek(50U);
  REQUIRE(std::get<0>(result) == 50);
  REQUIRE(std::get<1>(result) == Catch::Approx(50.0f));
}

TEST_CASE("peek() - does not trigger events", "[tween][peek]") {
  auto t = tweeny::from(0)
             .to(100)
             .during(100U)
             .build();

  int call_count = 0;
  t.on(tweeny::event::step, [&](auto&) {
    call_count++;
    return tweeny::event::response::ok;
  });

  (void)t.peek();
  (void)t.peek(50U);
  REQUIRE(call_count == 0);
}
