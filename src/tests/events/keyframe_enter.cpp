/*
This file is part of the Tweeny library.

Copyright (c) 2016-2026 Leonardo Guilherme Lucena de Freitas
Copyright (c) 2016 Guilherme R. Costa

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <catch2/catch_test_macros.hpp>
#include "tweeny/tweeny.h"

TEST_CASE("event::keyframeEnter - triggers when entering a new keyframe via step", "[event][keyframeEnter]") {
  auto t = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
  std::size_t entered_keyframe = 999;
  int call_count = 0;

  t.on(tweeny::event::keyframeEnter, [&](auto&, struct tweeny::event::keyframeEnter evt) {
    entered_keyframe = evt.key_frame;
    call_count++;
    return tweeny::event::response::ok;
  });

  t.step(31);

  REQUIRE(call_count == 1);
  REQUIRE(entered_keyframe == 1);
}

TEST_CASE("event::keyframeEnter - triggers when entering a new keyframe via seek", "[event][keyframeEnter]") {
  auto t = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
  std::size_t entered_keyframe = 999;
  int call_count = 0;

  t.on(tweeny::event::keyframeEnter, [&](auto&, struct tweeny::event::keyframeEnter evt) {
    entered_keyframe = evt.key_frame;
    call_count++;
    return tweeny::event::response::ok;
  });

  t.seek(35U);

  REQUIRE(call_count == 1);
  REQUIRE(entered_keyframe == 1);
}

TEST_CASE("event::keyframeEnter - triggers when entering a new keyframe via jump", "[event][keyframeEnter]") {
  auto t = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
  std::size_t entered_keyframe = 999;
  int call_count = 0;

  t.on(tweeny::event::keyframeEnter, [&](auto&, struct tweeny::event::keyframeEnter evt) {
    entered_keyframe = evt.key_frame;
    call_count++;
    return tweeny::event::response::ok;
  });

  t.jump(1);

  REQUIRE(call_count == 1);
  REQUIRE(entered_keyframe == 1);
}

TEST_CASE("event::keyframeEnter - does not trigger when staying in the same keyframe", "[event][keyframeEnter]") {
  auto t = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
  int call_count = 0;

  t.on(tweeny::event::keyframeEnter, [&](auto&, struct tweeny::event::keyframeEnter) {
    call_count++;
    return tweeny::event::response::ok;
  });

  t.step(10);
  t.step(5);
  t.step(10);

  REQUIRE(call_count == 0);
}

TEST_CASE("event::keyframeEnter - triggers for the correct keyframe in multi-keyframe tween", "[event][keyframeEnter]") {
  auto t = tweeny::from(0).to(25).during(10U).to(50).during(10U).to(75).during(10U).to(100).during(10U).build();
  std::vector<std::size_t> entered_keyframes;

  t.on(tweeny::event::keyframeEnter, [&](auto&, struct tweeny::event::keyframeEnter evt) {
    entered_keyframes.push_back(evt.key_frame);
    return tweeny::event::response::ok;
  });

  t.step(11);
  t.step(10);
  t.step(10);

  REQUIRE(entered_keyframes.size() == 3);
  REQUIRE(entered_keyframes[0] == 1);
  REQUIRE(entered_keyframes[1] == 2);
  REQUIRE(entered_keyframes[2] == 3);
}

TEST_CASE("event::keyframeEnter - can unsubscribe", "[event][keyframeEnter]") {
  auto t = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
  int call_count = 0;

  t.on(tweeny::event::keyframeEnter, [&](auto&, struct tweeny::event::keyframeEnter) {
    call_count++;
    return tweeny::event::response::unsubscribe;
  });

  t.step(31);
  t.seek(0U);
  t.step(31);

  REQUIRE(call_count == 1);
}

TEST_CASE("event::keyframeEnter - triggers when stepping backward into a different keyframe", "[event][keyframeEnter]") {
  auto t = tweeny::from(0).to(50).during(30U).to(100).during(30U).build();
  std::size_t entered_keyframe = 999;
  int call_count = 0;

  t.on(tweeny::event::keyframeEnter, [&](auto&, struct tweeny::event::keyframeEnter evt) {
    entered_keyframe = evt.key_frame;
    call_count++;
    return tweeny::event::response::ok;
  });

  t.step(35);
  call_count = 0;
  t.step(-10);

  REQUIRE(call_count == 1);
  REQUIRE(entered_keyframe == 0);
}
