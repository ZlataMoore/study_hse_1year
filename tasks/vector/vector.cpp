#include "vector.h"
#include <memory>
#include <cstring>

Vector::Vector() {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

Vector::Vector(size_t size) : data_(new int[size]()), size_(size), capacity_(size) {
}

Vector::Vector(std::initializer_list<ValueType> list) : Vector(list.size()) {
    size_t index = 0;
    for (auto element : list) {
        data_[index] = element;
        ++index;
    }
}

Vector::Vector(const Vector& other) : data_(new int[other.size_]), size_(other.size_), capacity_(other.capacity_) {
    for (size_t index = 0; index < size_; ++index) {
        data_[index] = other.data_[index];
    }
}

Vector::~Vector() {
    delete[] data_;
}

Vector& Vector::operator=(const Vector& other) {

    if (*this == other) {
        return *this;
    }
    capacity_ = other.capacity_;
    data_ = other.data_;
    size_ = other.size_;

    return *this;
}

const Vector::ValueType* Vector::Data() const {
    return data_;
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

Vector::ValueType& Vector::operator[](size_t position) {
    return data_[position];
}

const Vector::ValueType& Vector::operator[](size_t& position) const {
    return data_[position];
}

bool Vector::operator==(const Vector& array) const {
    if (size_ != array.size_) {
        return false;
    }
    for (size_t index = 0; index < size_; ++index) {
        if (data_[index] != array.data_[index]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (size_t index = 0; index < std::min(size_, other.size_); ++index) {
        if (data_[index] != other.data_[index]) {
            return data_[index] <=> other.data_[index];
        }
    }
    return size_ <=> other.size_;
}

void Vector::Reserve(Vector::SizeType new_capacity) {

    if (capacity_ < new_capacity) {
        auto* help = new int[new_capacity];
        capacity_ = new_capacity;
        for (size_t index = 0; index < size_; ++index) {
            help[index] = data_[index];
        }
        delete[] data_;
        data_ = help;
    }
}

void Vector::Swap(Vector& other) {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::PushBack(const Vector::ValueType& new_element) {
    Vector::SizeType new_capacity;
    if (capacity_ == size_) {
        if (capacity_ == 0) {
            new_capacity = 1;
        } else {
            new_capacity = 2 * capacity_;
        }
        this->Reserve(new_capacity);
    }
    data_[size_] = new_element;
    size_ += 1;
}

void Vector::PopBack() {
    size_ -= 1;
}
