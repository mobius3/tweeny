#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("event::step - callback is invoked on step()", "[event][step]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::step, [&](const auto &) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.step(1);
  REQUIRE(called == 1);
}

TEST_CASE("event::step - unsubscribe removes listener", "[event][step][unsubscribe]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::step, [&](const auto &) {
    ++called;
    return tweeny::event::response::unsubscribe;
  });

  t.on(tweeny::event::step, [&](const auto &) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.step(1);
  REQUIRE(called == 2);

  (void)t.step(1);
  REQUIRE(called == 3);
}
