#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

TEST_CASE("event::complete - triggered when reaching end via step", "[event][complete]") {
  auto t = tweeny::from(0).to(100).during(100U).build();

  bool completed = false;
  t.on(tweeny::event::complete, [&](auto&) {
    completed = true;
    return tweeny::event::response::ok;
  });

  // Not complete yet
  t.step(50);
  REQUIRE_FALSE(completed);

  // Complete now
  t.step(50);
  REQUIRE(completed);
}

TEST_CASE("event::complete - triggered when reaching end via seek", "[event][complete]") {
  auto t = tweeny::from(0).to(100).during(100U).build();

  bool completed = false;
  t.on(tweeny::event::complete, [&](auto&) {
    completed = true;
    return tweeny::event::response::ok;
  });

  t.seek(100U);
  REQUIRE(completed);
}

TEST_CASE("event::complete - triggered when jumping to last keyframe", "[event][complete]") {
  auto t = tweeny::from(0).to(50).during(50U).to(100).during(50U).build();

  bool completed = false;
  t.on(tweeny::event::complete, [&](auto&) {
    completed = true;
    return tweeny::event::response::ok;
  });

  t.jump(2);  // Jump to last keyframe
  REQUIRE(completed);
}

TEST_CASE("event::complete - not triggered when not at end", "[event][complete]") {
  auto t = tweeny::from(0).to(100).during(100U).build();

  bool completed = false;
  t.on(tweeny::event::complete, [&](auto&) {
    completed = true;
    return tweeny::event::response::ok;
  });

  t.step(50);
  REQUIRE_FALSE(completed);

  t.seek(75U);
  REQUIRE_FALSE(completed);
}

TEST_CASE("event::complete - can unsubscribe", "[event][complete]") {
  auto t = tweeny::from(0).to(100).during(100U).build();

  int call_count = 0;
  t.on(tweeny::event::complete, [&](auto&) {
    call_count++;
    return tweeny::event::response::unsubscribe;
  });

  t.seek(100U);
  REQUIRE(call_count == 1);

  // Reset and complete again - listener should be gone
  t.seek(0U);
  t.seek(100U);
  REQUIRE(call_count == 1);  // Should still be 1
}

TEST_CASE("event::complete - multiple listeners", "[event][complete]") {
  auto t = tweeny::from(0).to(100).during(100U).build();

  int listener1_count = 0;
  int listener2_count = 0;

  t.on(tweeny::event::complete, [&](auto&) {
    listener1_count++;
    return tweeny::event::response::ok;
  });

  t.on(tweeny::event::complete, [&](auto&) {
    listener2_count++;
    return tweeny::event::response::ok;
  });

  t.step(100);
  REQUIRE(listener1_count == 1);
  REQUIRE(listener2_count == 1);
}

TEST_CASE("event::complete - triggered on exact completion", "[event][complete]") {
  auto t = tweeny::from(0).to(100).during(100U).build();

  bool completed = false;
  t.on(tweeny::event::complete, [&](auto& tween) {
    REQUIRE(tween.progress() >= 1.0f);
    REQUIRE(tween.peek() == 100);
    completed = true;
    return tweeny::event::response::ok;
  });

  t.step(100);
  REQUIRE(completed);
}
