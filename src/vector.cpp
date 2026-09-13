#include <stdexcept>
#include <string>
#include "vector.hpp"


Vector::Vector(): size_{0}, contents_{new double[0]} {};

Vector::Vector(int size): size_{size}, contents_{new double[size]} {
    for (int i = 0; i < size; ++i) {contents_[i] = 0;}
}

Vector::Vector(const Vector& other): size_{other.size_}, 
                                     contents_{new double[other.size_]} {
    for (int i = 0; i < other.size_; ++i) {
        contents_[i] = other.contents_[i];
    }
}

Vector::Vector(Vector&& other) noexcept: size_{other.size_}, 
                                contents_{other.contents_} {
    other.contents_ = nullptr;
    other.size_ = 0;
}

Vector::~Vector() {delete[] contents_;}

Vector& Vector::operator=(const Vector& other) {
    if (this==&other) {
        return *this;
    }

    delete[] contents_;
    contents_ = new double[other.size_];

    for (int i = 0; i < other.size_; ++i) {
        contents_[i] = other.contents_[i];
    }

    size_ = other.size_;
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this==&other) {
        return *this;
    }

    delete[] contents_;
    contents_ = other.contents_;
    size_ = other.size_;
    other.contents_ = nullptr;
    other.size_ = 0;
    return *this;
}

double Vector::operator[](int i) const noexcept {return contents_[i];}
double& Vector::operator[](int i) noexcept {return contents_[i];}

Vector Vector::operator+(const Vector& other) const {
    if (size_ != other.size()) {
        throw std::invalid_argument(
            "Vector length mismatch: argument 0 has length " + std::to_string(size_)
            + ", but argument 1 has length " + std::to_string(other.size())
        );
    }

    Vector res = Vector(size_);

    for (int i = 0; i < other.size_; ++i) {
        res[i] = contents_[i] + other.contents_[i];
    }

    return res;
}

int Vector::size() const noexcept {return size_;}