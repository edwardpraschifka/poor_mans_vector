#include "vector.hpp"

Vector::Vector(int size): size_{size}, contents_{new double[size]} {
}

Vector::~Vector() {
    delete[] contents_;
}

int Vector::size() const {
    return size_;
}