#pragma once

#include <compare>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>

class Vector {
public:
    using ValueType = int;
    using SizeType = size_t;
    using DifferenceType = ptrdiff_t;

    class Iterator {
    private:
        int* current_;

    public:
        explicit Iterator(ValueType* pointer) : current_(pointer) {
        }

        Iterator() {
            current_ = 0;
        }

        ValueType& operator*() const {
            return *current_;
        }

        ValueType* operator->() const {
            return current_;
        }

        Iterator& operator=(Iterator other) {
            current_ = other.current_;
            return *this;
        }

        Iterator& operator=(int* other) {
            current_ = other;
            return *this;
        }

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy(*this);
            ++current_;
            return copy;
        }

        Iterator& operator--() {
            --current_;
            return *this;
        }
        Iterator operator--(int) {
            Iterator copy(*this);
            --current_;
            return copy;
        }

        Iterator operator+(DifferenceType shift) {
            Iterator result;
            result = current_ + shift;
            return result;
        }

        DifferenceType operator-(Iterator other) {
            DifferenceType result;
            result = current_ - other.current_;
            return result;
        }
        Iterator& operator+=(DifferenceType shift) {
            current_ += shift;
            return *this;
        }

        Iterator& operator-=(DifferenceType shift) {
            current_ -= shift;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }
        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }
        std::strong_ordering operator<=>(const Iterator& other) const {
            if (current_ < other.current_) {
                return std::strong_ordering::less;
            } else if (current_ == other.current_) {
                return std::strong_ordering::equal;
            } else {
                return std::strong_ordering::greater;
            }
        }
    };

    Vector();
    explicit Vector(size_t size);
    Vector(std::initializer_list<ValueType> list);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    ~Vector();

    SizeType Size() const;
    SizeType Capacity() const;

    const ValueType* Data() const;

    ValueType& operator[](size_t position);
    const ValueType& operator[](size_t& position) const;

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    std::strong_ordering operator<=>(const Vector& other) const;

    void Reserve(SizeType new_capacity);
    void Clear();

    void PushBack(const ValueType& new_element);
    void PopBack();

    void Swap(Vector& other);

    Iterator Begin() {
        return Iterator(data_);
    }
    Iterator End() {
        return Iterator(data_ + size_);
    }

    Iterator begin() {  // NOLINT
        return Iterator(data_);
    }
    Iterator end() {  // NOLINT
        return Iterator(data_ + size_);
    }

private:
    int* data_;
    size_t size_;
    size_t capacity_;
};
