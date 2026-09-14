#include <cstdint>
#include <stdexcept>
#include <string>
#include "iterator.hpp"

template <typename T>
class Vector {
    private:
        int size_;
        T* contents_;

    public:
        // constructors, destructors
        Vector();
        Vector(int size);
        Vector(const Vector& other);
        Vector(Vector&& other) noexcept;
        ~Vector();

        // assignment
        Vector& operator=(const Vector& other);
        Vector& operator=(Vector&& other) noexcept;

        // indexing
        T operator[](int i) const noexcept;
        T& operator[](int i) noexcept;
        T& at(int i);
        T at(int i) const;

        // addition
        Vector operator+(const Vector& other) const;
        
        // iterators
        Iterator<T> begin() const;
        Iterator<T> end() const;

        // getters
        int size() const noexcept;
        
};

template <typename T>
Vector<T>::Vector(): size_{0}, contents_{new T[0]} {};

template <typename T>
Vector<T>::Vector(int size): size_{size}, contents_{new T[size]} {
    for (int i = 0; i < size; ++i) {contents_[i] = T{};}
}

template <typename T>
Vector<T>::Vector(const Vector& other): size_{other.size_}, 
                                     contents_{new T[other.size_]} {
    for (int i = 0; i < other.size_; ++i) {
        contents_[i] = other.contents_[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept: size_{other.size_}, 
                                contents_{other.contents_} {
    other.contents_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Vector<T>::~Vector() {delete[] contents_;}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this==&other) {
        return *this;
    }

    delete[] contents_;
    contents_ = new T[other.size_];

    for (int i = 0; i < other.size_; ++i) {
        contents_[i] = other.contents_[i];
    }

    size_ = other.size_;
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
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

template <typename T>
T Vector<T>::operator[](int i) const noexcept {return contents_[i];}

template <typename T>
T& Vector<T>::operator[](int i) noexcept {return contents_[i];}

template <typename T>
T& Vector<T>::at(int i) {
    if ((i < 0) || (i >= size_)) {
        throw std::out_of_range(
            "Invalid index: tried to access index " + std::to_string(i)
            + " (valid indices are between 0 and " + std::to_string(size_ - 1) + ")"
        );
    }

    return contents_[i];
}

template <typename T>
T Vector<T>::at(int i) const {    
    return const_cast<Vector*>(this)->at(i);
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector& other) const {
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

template <typename T>
Iterator<T> Vector<T>::begin() const {
    return Iterator<T>(contents_);
}

template <typename T>
Iterator<T> Vector<T>::end() const {
    return Iterator<T>(contents_ + size_);
}

template <typename T>
int Vector<T>::size() const noexcept {return size_;}