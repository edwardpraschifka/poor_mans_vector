#include <catch2/catch_test_macros.hpp>
#include "vector.hpp"

TEST_CASE("Vector constructs with correct size") {
    Vector v(5);
    REQUIRE(v.size() == 5);
}

TEST_CASE("Vector elements are initialized to zero") {
    const Vector v(10);
    int sz = v.size();
    
    for (int i = 0; i < sz; ++i){
        REQUIRE(v[i] == 0);
    }
}

TEST_CASE("Can assign new values to non-const vector") {
    Vector v(3);
    int sz = v.size();
    
    for (int i = 0; i < sz; ++i){
        v[i] = i+1;
    }

    for (int i = 0; i < sz; ++i){
        REQUIRE(v[i] == i+1);
    }
}