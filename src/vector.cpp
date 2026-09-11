#include "vector.hpp"

Vector::Vector(int size): size_{size}, contents_{new double[size]} {
    for (int i = 0; i < size; ++i) contents_[i] = 0;
}

Vector::Vector(): size_{0}, contents_{new double[0]} {};

Vector::~Vector() {
    delete[] contents_;
}

double Vector::operator[](int i) const {
    return contents_[i];
}

double& Vector::operator[](int i) {
    return contents_[i];
}

int Vector::size() const {
    return size_;
}