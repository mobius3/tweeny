#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("event::update - callback is invoked on step()", "[event][update]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::update, [&](const auto &) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.step(1);
  REQUIRE(called == 1);
}

TEST_CASE("event::update - callback is invoked on seek()", "[event][update]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::update, [&](const auto &) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.seek(5U);
  REQUIRE(called == 1);
}

TEST_CASE("event::update - callback is invoked on jump()", "[event][update]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::update, [&](const auto &) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.jump(1);
  REQUIRE(called == 1);
}

TEST_CASE("event::update - callback fires after specific event", "[event][update]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int step_order = 0;
  int update_order = 0;
  int counter = 0;

  t.on(tweeny::event::step, [&](const auto &) {
    step_order = ++counter;
    return tweeny::event::response::ok;
  });

  t.on(tweeny::event::update, [&](const auto &) {
    update_order = ++counter;
    return tweeny::event::response::ok;
  });

  (void)t.step(1);
  REQUIRE(step_order == 1);
  REQUIRE(update_order == 2);
}

TEST_CASE("event::update - callback fires before complete event", "[event][update]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int update_order = 0;
  int complete_order = 0;
  int counter = 0;

  t.on(tweeny::event::update, [&](const auto &) {
    update_order = ++counter;
    return tweeny::event::response::ok;
  });

  t.on(tweeny::event::complete, [&](const auto &) {
    complete_order = ++counter;
    return tweeny::event::response::ok;
  });

  (void)t.step(10);
  REQUIRE(update_order == 1);
  REQUIRE(complete_order == 2);
}

TEST_CASE("event::update - unsubscribe removes listener", "[event][update]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::update, [&](const auto &) {
    ++called;
    return tweeny::event::response::unsubscribe;
  });

  t.on(tweeny::event::update, [&](const auto &) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.step(1);
  REQUIRE(called == 2);

  (void)t.step(1);
  REQUIRE(called == 3);
}

TEST_CASE("event::update - fires on all update types in sequence", "[event][update]") {
  auto t = tweeny::from(0)
             .to(10)
             .during(10U)
             .to(20)
             .during(10U)
             .build();

  int called = 0;

  t.on(tweeny::event::update, [&](const auto &) {
    ++called;
    return tweeny::event::response::ok;
  });

  (void)t.step(1);
  REQUIRE(called == 1);

  (void)t.seek(5U);
  REQUIRE(called == 2);

  (void)t.jump(1);
  REQUIRE(called == 3);
}
