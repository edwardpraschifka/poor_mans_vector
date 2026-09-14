#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "vector.hpp"

float foo(float i) {
    return (i*i) + 7;
}

float bar(float i) {
    return (i - 1) * 4;
}

TEMPLATE_TEST_CASE("Vector constructs with correct size", "[vector]", int, float) {
    Vector<TestType> v(5);
    Vector<TestType> w;
    Vector<TestType> x(10);
    REQUIRE(v.size() == 5);
    REQUIRE(w.size() == 0);
    REQUIRE(x.size() == 10);
}

TEMPLATE_TEST_CASE("Vector elements are initialized to T's default value", "[vector]", int, float) {
    const Vector<TestType> v(10);
    int sz = v.size();
    
    for (int i = 0; i < sz; ++i){
        REQUIRE(v[i] == TestType{});
    }
}

TEMPLATE_TEST_CASE("Can assign new values to non-const Vector", "[vector]", int, float) {
    Vector<TestType> v(3);
    int sz = v.size();
    
    for (int i = 0; i < sz; ++i){
        v[i] = foo(i);
    }

    for (int i = 0; i < sz; ++i){
        REQUIRE(v[i] == foo(i));
    }
}

TEMPLATE_TEST_CASE("Can construct a new Vector using copy constructor", "[vector]", int, float) {
    Vector<TestType> v(3);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = foo(i);
    }

    Vector<TestType> w = Vector<TestType>(v);

    for (int i = 0; i < sz; ++i){
        REQUIRE(w[i] == foo(i));
    }
}

TEMPLATE_TEST_CASE("Can assign one Vector to another using copy assignment operator", "[vector]", int, float) {
    Vector<TestType> v(3);
    Vector<TestType> w(5);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = foo(i);
    }

    w = v;

    for (int i = 0; i < sz; ++i){
        REQUIRE(w[i] == foo(i));
    }
}

TEMPLATE_TEST_CASE("Can assign a Vector to itself using copy assignment operator", "[vector]", int, float) {
    Vector<TestType> v(3);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = foo(i);
    }

    v = v;

    for (int i = 0; i < sz; ++i){
        REQUIRE(v[i] == foo(i));
    }
}

TEMPLATE_TEST_CASE("Can construct a new Vector using move constructor", "[vector]", int, float) {
    Vector<TestType> v(3);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = foo(i);
    }

    Vector<TestType> w = std::move(v);

    REQUIRE(v.size() == 0);
    REQUIRE(w.size() == sz);

    for (int i = 0; i < sz; ++i){
        REQUIRE(w[i] == foo(i));
    }
}

TEMPLATE_TEST_CASE("Can assign one Vector to another using move assignment operator", "[vector]", int, float) {
    Vector<TestType> v(3);
    Vector<TestType> w(5);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = foo(i);
    }

    w = std::move(v);

    REQUIRE(v.size() == 0);
    REQUIRE(w.size() == sz);

    for (int i = 0; i < sz; ++i){
        REQUIRE(w[i] == foo(i));
    }
}

TEMPLATE_TEST_CASE("Can assign a Vector  to itself using move assignment operator", "[vector]", int, float) {
    Vector<TestType> v(3);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = foo(i);
    }

    v = std::move(v);

    REQUIRE(v.size() == sz);

    for (int i = 0; i < sz; ++i){
        REQUIRE(v[i] == foo(i));
    }
}

TEMPLATE_TEST_CASE("Can add two Vectors", "[vector]", int, float) {
    Vector<TestType> v(5);
    Vector<TestType> w(5);
    Vector<TestType> res;
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = foo(i);
        w[i] = bar(i);
    }

    res = v + w;

    REQUIRE(res.size() == sz);

    for (int i = 0; i < sz; ++i){
        REQUIRE(res[i] == foo(i) + bar(i));
    }
}

TEMPLATE_TEST_CASE("Try to add two Vectors of different length", "[vector]", int, float) {
    Vector<TestType> v(5);
    Vector<TestType> w(3);
    REQUIRE_THROWS_AS(v + w, std::invalid_argument);
}

TEMPLATE_TEST_CASE("Try using at() method to read a const Vector", "[vector]", int, float) {
    Vector<TestType> v = Vector<TestType>(5);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v[i] = foo(i);
    }

    const Vector<TestType> w(v);

    for (int i = 0; i < sz; ++i){
        REQUIRE(w[i] == foo(i));
    }
}

TEMPLATE_TEST_CASE("Try using at() method to write & read to a non-const Vector", "[vector]", int, float) {
    Vector<TestType> v(5);
    int sz = v.size();

    for (int i = 0; i < sz; ++i){
        v.at(i) = foo(i);
    }

    for (int i = 0; i < sz; ++i){
        REQUIRE(v[i] == foo(i));
    }
}

TEMPLATE_TEST_CASE("Try using at() method with out-of-bounds indices", "[vector]", int, float) {
    Vector<TestType> v(5);
    REQUIRE_THROWS_AS(v.at(-1), std::out_of_range);
    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
    REQUIRE_THROWS_AS(v.at(100), std::out_of_range);
}