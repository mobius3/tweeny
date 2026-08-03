#include <catch2/catch_test_macros.hpp>
#include <tweeny/easing.h>

#include "test-easing.h"

TEST_CASE("easing::backIn matches Penner easeInBack samples", "[easing][back]") {
  test_easing(tweeny::easing::backIn, easeInBack);
}

TEST_CASE("easing::backOut matches Penner easeOutBack samples", "[easing][back]") {
  test_easing(tweeny::easing::backOut, easeOutBack);
}

TEST_CASE("easing::backInOut matches Penner easeInOutBack samples", "[easing][back]") {
  test_easing(tweeny::easing::backInOut, easeInOutBack);
}

TEST_CASE("tween via(backIn) matches Penner easeInBack samples", "[easing][back][tween]") {
  test_tween_easing(tweeny::easing::backIn, easeInBack);
}

TEST_CASE("tween via(backOut) matches Penner easeOutBack samples", "[easing][back][tween]") {
  test_tween_easing(tweeny::easing::backOut, easeOutBack);
}

TEST_CASE("tween via(backInOut) matches Penner easeInOutBack samples", "[easing][back][tween]") {
  test_tween_easing(tweeny::easing::backInOut, easeInOutBack);
}
