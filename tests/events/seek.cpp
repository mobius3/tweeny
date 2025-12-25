#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("event::seek - callback is invoked on seek()", "[event][seek]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::seek, [&](const auto &) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.seek(5U);
  REQUIRE(called == 1);
}
