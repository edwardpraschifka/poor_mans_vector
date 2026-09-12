#include <catch2/catch_test_macros.hpp>
#include "vector.hpp"

TEST_CASE("Vector constructs with correct size") {
    Vector v(5);
    Vector w;
    Vector x(10);
    REQUIRE(v.size() == 5);
    REQUIRE(w.size() == 0);
    REQUIRE(x.size() == 10);
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

TEST_CASE("Can construct a new vector using copy constructor") {
    Vector v(3);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = i+1;
    }

    Vector w = Vector(v);

    for (int i = 0; i < sz; ++i){
        REQUIRE(w[i] == i+1);
    }
}

TEST_CASE("Can assign one vector to another using copy assignment operator") {
    Vector v(3);
    Vector w(5);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = i+1;
    }

    w = v;

    for (int i = 0; i < sz; ++i){
        REQUIRE(w[i] == i+1);
    }
}

TEST_CASE("Can assign a vector to itself using copy assignment operator") {
    Vector v(3);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = i+1;
    }

    v = v;

    for (int i = 0; i < sz; ++i){
        REQUIRE(v[i] == i+1);
    }
}