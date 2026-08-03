#ifndef TWEENY_TESTS_EASINGS_TEST_EASING_H
#define TWEENY_TESTS_EASINGS_TEST_EASING_H

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <tweeny/tweeny.h>

#include "reference-values.h"

template <typename Easing>
void test_easing(const Easing & easing, const float (&reference)[sample_count]) {
  for (std::size_t t = 0; t < sample_count; ++t) {
    const float position = static_cast<float>(t) / 100.f;
    const float got = easing(position, 0.f, 1.f);
    REQUIRE(got == Catch::Approx(reference[t]).margin(1e-6f));
  }
}

template <typename Easing>
void test_tween_easing(const Easing & easing, const float (&reference)[sample_count]) {
  auto tween = tweeny::from(0.f).to(1.f).via(easing).during(100U).build();
  for (std::size_t t = 0; t < sample_count; ++t) {
    const float got = tween.peek(static_cast<uint32_t>(t));
    REQUIRE(got == Catch::Approx(reference[t]).margin(1e-6f));
  }
}

#endif // TWEENY_TESTS_EASINGS_TEST_EASING_H
