#include <catch2/catch_test_macros.hpp>
#include "vector.hpp"

TEST_CASE("Vector constructs with correct size") {
    Vector v(5);
    REQUIRE(v.size() == 5);
}