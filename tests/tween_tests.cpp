#include <catch2/catch_test_macros.hpp>
#include "tweeny.h"

namespace {
    constexpr float eps = 1e-4f;
    bool approxf(const float a, const float b) { return std::fabs(a - b) <= eps; }
}

TEST_CASE("tween - step by duration (time-based)", "[tween][step][duration]") {
    auto tw = tweeny::from(0.0f).to(100.0f).during(100).via(tweeny::easing::linear);
    REQUIRE(tw.duration() == 100);
    REQUIRE(approxf(tw.progress(), 0.0f));

    SECTION("25% progress at t=25") {
        tw.step(25u);
        REQUIRE(approxf(tw.progress(), 0.25f));
        REQUIRE(approxf(tw.peek(), 25.0f));
    }
    SECTION("halfway at t=50") {
        tw.step(50u);
        REQUIRE(approxf(tw.progress(), 0.5f));
        REQUIRE(approxf(tw.peek(), 50.0f));
    }
    SECTION("full at t=100 clamps to 1.0") {
        tw.step(100u);
        REQUIRE(approxf(tw.progress(), 1.0f));
        REQUIRE(approxf(tw.peek(), 100.0f));
    }
}

TEST_CASE("tween - step by progress (fractional)", "[tween][step][progress]") {
    auto tw = tweeny::from(0.0f).to(100.0f).during(100).via(tweeny::easing::linear);
    REQUIRE(approxf(tw.progress(), 0.0f));

    SECTION("step by 0.25") {
        tw.step(0.25f);
        REQUIRE(approxf(tw.progress(), 0.25f));
        REQUIRE(approxf(tw.peek(), 25.0f));
    }
    SECTION("two steps of 0.5 saturate at 1.0") {
        tw.step(0.5f);
        tw.step(0.75f); // this should saturate to 1.0 overall
        REQUIRE(approxf(tw.progress(), 1.0f));
        REQUIRE(approxf(tw.peek(), 100.0f));
    }
}

TEST_CASE("tween - seek to absolute progress and time", "[tween][seek]") {
    auto tw = tweeny::from(0.0f).to(100.0f).during(200).via(tweeny::easing::linear);

    SECTION("seek by progress") {
        tw.seek(0.5f);
        REQUIRE(approxf(tw.progress(), 0.5f));
        REQUIRE(approxf(tw.peek(), 50.0f));
    }

    SECTION("seek by time") {
        tw.seek(50u);
        REQUIRE(approxf(tw.progress(), 0.25f));
        REQUIRE(approxf(tw.peek(), 25.0f));
        tw.seek(200u);
        REQUIRE(approxf(tw.progress(), 1.0f));
        REQUIRE(approxf(tw.peek(), 100.0f));
    }
}

TEST_CASE("tween - multiple points: jump and point indexing", "[tween][jump][points]") {
    auto tw = tweeny::from(0.0f)
        .to(50.0f).during(100).via(tweeny::easing::linear)
        .to(100.0f).during(100).via(tweeny::easing::linear);

    REQUIRE(tw.point() == 0);

    SECTION("jump to point 1 goes to second segment start") {
        const auto & v = tw.jump(1);
        REQUIRE(tw.point() == 1);
        REQUIRE(approxf(v, 50.0f));
        REQUIRE(approxf(tw.progress(), 0.5f));
    }

    SECTION("jump to point 1 then step progresses within that segment") {
        tw.jump(1);
        tw.step(50u); // half of 100
        REQUIRE(tw.point() == 1);
        REQUIRE(approxf(tw.progress(), 0.75f));
        REQUIRE(approxf(tw.peek(), 75.0f));
    }
}

TEST_CASE("tween - callbacks onStep/onSeek", "[tween][callbacks]") {
    auto tw = tweeny::from(0.0f).to(100.0f).during(100).via(tweeny::easing::linear);

    int stepCalls = 0;
    int seekCalls = 0;
    float lastValue = -1.0f;

    tw.onStep([&](auto & /*t*/, float v) {
        ++stepCalls;
        lastValue = v;
        return true;
    });

    tw.onSeek([&](auto & /*t*/, float v) {
        ++seekCalls;
        lastValue = v;
        return true;
    });

    SECTION("onStep triggers on time step") {
        tw.step(25u);
        REQUIRE(stepCalls >= 1);
        REQUIRE(approxf(lastValue, 25.0f));
    }

    SECTION("onSeek triggers on seek") {
        tw.seek(0.5f);
        REQUIRE(seekCalls >= 1);
        REQUIRE(approxf(lastValue, 50.0f));
    }

    SECTION("suppressed callbacks do not fire") {
        stepCalls = seekCalls = 0;
        tw.seek(0.25f, true);
        tw.step(25u, true);
        REQUIRE(stepCalls == 0);
        REQUIRE(seekCalls == 0);
    }
}

TEST_CASE("tween - heterogeneous values (linear, equal durations)", "[tween][heterogeneous][linear]") {
    // x, y, scale, alpha
    auto tw = tweeny::from(0.0f, 400.0f, 0.5f, 0.0f)
        .to(100.0f, 100.0f, 1.0f, 1.0f)
        .during(300, 300, 300, 300)
        .via(tweeny::easing::linear);

    // Halfway through time should be halfway in values for all components
    auto [x, y, s, a] = tw.step(150u);
    REQUIRE(approxf(x, 50.0f));
    REQUIRE(approxf(y, 250.0f));
    REQUIRE(approxf(s, 0.75f));
    REQUIRE(approxf(a, 0.5f));

    // peek() should match current and not change state
    const auto & cur = tw.peek();
    REQUIRE(approxf(std::get<0>(cur), x));
    REQUIRE(approxf(std::get<1>(cur), y));
    REQUIRE(approxf(std::get<2>(cur), s));
    REQUIRE(approxf(std::get<3>(cur), a));

    // Absolute peek by time (end)
    auto endVals = tw.peek(300u);
    REQUIRE(approxf(std::get<0>(endVals), 100.0f));
    REQUIRE(approxf(std::get<1>(endVals), 100.0f));
    REQUIRE(approxf(std::get<2>(endVals), 1.0f));
    REQUIRE(approxf(std::get<3>(endVals), 1.0f));
}

TEST_CASE("tween - mixed types (float, int) with linear easing and rounding", "[tween][heterogeneous][int]") {
    auto tw = tweeny::from(0.0f, 0)
        .to(10.0f, 10)
        .during(100)
        .via(tweeny::easing::linear);

    auto [f, i] = tw.step(50u);
    REQUIRE(approxf(f, 5.0f));
    REQUIRE(i == 5); // integral branch rounds
}

TEST_CASE("tween - per-component durations saturate independently", "[tween][heterogeneous][durations]") {
    // First component finishes 4x faster than the second
    auto tw = tweeny::from(0.0f, 0.0f)
        .to(10.0f, 10.0f)
        .during(50, 200)
        .via(tweeny::easing::linear);

    // At t=50: first should be complete; second should be at 0.25
    auto [a, b] = tw.seek(50u);
    REQUIRE(approxf(a, 10.0f));
    REQUIRE(approxf(b, 2.5f));

    // At t=200: both complete
    auto [a2, b2] = tw.seek(200u);
    REQUIRE(approxf(a2, 10.0f));
    REQUIRE(approxf(b2, 10.0f));
}

TEST_CASE("tween - via(index) overrides easing for a specific segment (stepped)", "[tween][via-index][stepped]") {
    // Build two segments; leave first as default (linear for float), set second as stepped
    auto tw = tweeny::from(0.0f)
        .to(100.0f).during(100)
        .to(200.0f).during(100);
    tw.via(1, tweeny::easing::stepped);

    // Middle of first segment: linear 0 -> 100
    REQUIRE(approxf(tw.seek(50u), 50.0f));

    // Middle of second segment (t=150): stepped keeps start value (100)
    REQUIRE(approxf(tw.seek(150u), 100.0f));

    // End clamps to final
    REQUIRE(approxf(tw.seek(200u), 200.0f));
}

TEST_CASE("tween - direction forward/backward and seek unaffected", "[tween][direction]") {
    auto tw = tweeny::from(0.0f).to(100.0f).during(100).via(tweeny::easing::linear);

    tw.forward();
    tw.step(25u);
    REQUIRE(approxf(tw.progress(), 0.25f));
    REQUIRE(approxf(tw.peek(), 25.0f));

    tw.backward();
    tw.step(25u);
    REQUIRE(approxf(tw.progress(), 0.0f));
    REQUIRE(approxf(tw.peek(), 0.0f));

    // Seek should ignore direction and set absolute time/progress
    tw.backward();
    tw.seek(50u);
    REQUIRE(approxf(tw.progress(), 0.5f));
    REQUIRE(approxf(tw.peek(), 50.0f));
}

TEST_CASE("tween - peek(progress/time) does not mutate state", "[tween][peek]") {
    auto tw = tweeny::from(0.0f).to(100.0f).during(100).via(tweeny::easing::linear);
    REQUIRE(approxf(tw.progress(), 0.0f));

    auto p0 = tw.progress();
    auto pv = tw.peek(0.5f);
    (void)pv;
    REQUIRE(approxf(tw.progress(), p0));

    auto pv2 = tw.peek(50u);
    (void)pv2;
    REQUIRE(approxf(tw.progress(), p0));
}

TEST_CASE("tween - multi-point timeline scrubbing and point indexing (linear)", "[tween][timeline][seek][point]") {
    auto tl = tweeny::from(0.0f)
        .to(100.0f).during(200).via(tweeny::easing::linear)   // segment 0
        .to(200.0f).during(400).via(tweeny::easing::linear)   // segment 1
        .to(300.0f).during(400).via(tweeny::easing::linear);  // segment 2

    // t=100: middle of segment 0
    REQUIRE(approxf(tl.seek(100u), 50.0f));
    REQUIRE(tl.point() == 0);

    // t=300: 100 into seg0 + 200 into seg1 (half of seg1)
    REQUIRE(approxf(tl.seek(300u), 150.0f));
    REQUIRE(tl.point() == 1);

    // t=900: 1000 total; 300 into seg2 (half of seg2)
    REQUIRE(approxf(tl.seek(900u), 250.0f));
    REQUIRE(tl.point() == 2);
}

TEST_CASE("tween - callbacks one-shot removal semantics", "[tween][callbacks][removal]") {
    SECTION("onStep one-shot") {
        auto tw = tweeny::from(0).to(100).during(100).via(tweeny::easing::linear);
        int calls = 0;
        tw.onStep([&](auto &, int) {
            ++calls;
            return true; // remove after first call
        });

        tw.step(10u);
        tw.step(10u);
        REQUIRE(calls == 1);
    }

    SECTION("onSeek one-shot") {
        auto tw = tweeny::from(0.0f).to(1.0f).during(100).via(tweeny::easing::linear);
        int calls = 0;
        tw.onSeek([&](auto &, float) {
            ++calls;
            return true; // remove after first call
        });

        tw.seek(0.25f);
        tw.seek(0.5f);
        REQUIRE(calls == 1);
    }
}
