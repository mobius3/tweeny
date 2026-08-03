#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>
#include <tweeny/tweeny.h>

namespace {

template <typename Easing>
void require_seek_step_match_peek(Easing easing) {
  auto probe = tweeny::from(0.f).to(1.f).via(easing).during(100U).build();
  auto seeker = tweeny::from(0.f).to(1.f).via(easing).during(100U).build();
  auto stepper = tweeny::from(0.f).to(1.f).via(easing).during(100U).build();

  for (uint32_t frame = 0; frame <= 100U; ++frame) {
    const auto expected = probe.peek(frame);

    REQUIRE(seeker.seek(frame) == Catch::Approx(expected).margin(1e-6f));
    REQUIRE(seeker.peek() == Catch::Approx(expected).margin(1e-6f));

    stepper.seek(0U);
    REQUIRE(stepper.step(frame) == Catch::Approx(expected).margin(1e-6f));
    REQUIRE(stepper.peek() == Catch::Approx(expected).margin(1e-6f));
  }
}

template <typename Easing>
void require_jump_seek_match_peek(Easing easing) {
  auto t = tweeny::from(0.f)
             .to(0.5f).via(easing).during(50U)
             .to(1.f).via(easing).during(50U)
             .build();
  auto seeker = tweeny::from(0.f)
                  .to(0.5f).via(easing).during(50U)
                  .to(1.f).via(easing).during(50U)
                  .build();

  constexpr uint32_t positions[] = {0U, 50U, 100U};
  for (int i = 0; i < 3; ++i) {
    const auto pos = positions[i];
    const auto expected = t.peek(pos);

    REQUIRE(t.jump(i) == Catch::Approx(expected).margin(1e-6f));
    REQUIRE(t.peek() == Catch::Approx(expected).margin(1e-6f));
    REQUIRE(seeker.seek(pos) == Catch::Approx(expected).margin(1e-6f));
    REQUIRE(seeker.peek() == Catch::Approx(expected).margin(1e-6f));
  }
}

}  // namespace

TEST_CASE("navigation_consistency - seek/step agree with peek across easings", "[tween][navigation][navigation_consistency]") {
  SECTION("linear") { require_seek_step_match_peek(tweeny::easing::linear); }
  SECTION("def") { require_seek_step_match_peek(tweeny::easing::def); }
  SECTION("stepped") { require_seek_step_match_peek(tweeny::easing::stepped); }
  SECTION("quadraticIn") { require_seek_step_match_peek(tweeny::easing::quadraticIn); }
  SECTION("cubicOut") { require_seek_step_match_peek(tweeny::easing::cubicOut); }
  SECTION("bounceOut") { require_seek_step_match_peek(tweeny::easing::bounceOut); }
  SECTION("elasticIn") { require_seek_step_match_peek(tweeny::easing::elasticIn); }
  SECTION("backIn") { require_seek_step_match_peek(tweeny::easing::backIn); }
}

TEST_CASE("navigation_consistency - jump/seek agree with peek at keyframes across easings", "[tween][navigation][navigation_consistency]") {
  SECTION("linear") { require_jump_seek_match_peek(tweeny::easing::linear); }
  SECTION("def") { require_jump_seek_match_peek(tweeny::easing::def); }
  SECTION("stepped") { require_jump_seek_match_peek(tweeny::easing::stepped); }
  SECTION("quadraticIn") { require_jump_seek_match_peek(tweeny::easing::quadraticIn); }
  SECTION("cubicOut") { require_jump_seek_match_peek(tweeny::easing::cubicOut); }
  SECTION("bounceOut") { require_jump_seek_match_peek(tweeny::easing::bounceOut); }
  SECTION("elasticIn") { require_jump_seek_match_peek(tweeny::easing::elasticIn); }
  SECTION("backIn") { require_jump_seek_match_peek(tweeny::easing::backIn); }
}
