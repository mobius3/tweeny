#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("event::jump - callback is invoked on jump()", "[event][jump]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::jump, [&](const auto &) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.jump(1);
  REQUIRE(called == 1);
}
