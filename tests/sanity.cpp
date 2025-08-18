#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("sanity - the test framework runs", "[sanity]") {
    REQUIRE(1 + 1 == 2);
}
TEST_CASE("sanity") {
    REQUIRE(1 + 1 == 2);
}
