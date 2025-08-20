#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>
#include <tweeny/event.h>

TEST_CASE("event::step - callback is invoked on step()", "[event][step]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::step, [&](tweeny::tween<int>&) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.step(1);
  REQUIRE(called == 1);
}
