#include "shortarray.hpp"
#include <algorithm>
#include <iostream>


ShortArray::ShortArray()
    : data_(nullptr), capacity_(0), size_(0) {}


ShortArray::ShortArray(size_t initial_size, short fill_value)
    : size_(initial_size), capacity_(initial_size) {
    data_ = new short[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = fill_value;
    }
}


ShortArray::ShortArray(const ShortArray& other)
    : size_(other.size_), capacity_(other.capacity_) {
    data_ = new short[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
}


ShortArray& ShortArray::operator=(const ShortArray& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new short[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    return *this;
}


ShortArray::ShortArray(ShortArray&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = other.capacity_ = 0;
}


ShortArray& ShortArray::operator=(ShortArray&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }
    return *this;
}


ShortArray::~ShortArray() {
    delete[] data_;
}


void ShortArray::push(short new_val) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        short* new_data = new short[new_capacity];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
    data_[size_++] = new_val;
}


short ShortArray::pop() {
    if (size_ == 0) {
        throw std::out_of_range("Cannot pop from an empty array");
    }

    // data_[size_] = 0; // Not necessary here, because size_ matters, not capacity_, so it won't be touched
    return data_[--size_];
}


size_t ShortArray::size() const {
    return size_;
}


void ShortArray::resize(size_t new_size, short fill_value) {
    if (new_size > capacity_) {
        short* new_data = new short[new_size];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_size;
    }

    for (size_t i = size_; i < new_size; ++i) {
        data_[i] = fill_value;
    }

    size_ = new_size;
}


short& ShortArray::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

const short& ShortArray::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}


std::ostream& operator<<(std::ostream& os, const ShortArray& arr) {
    os << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        os << arr[i];
        if (i != arr.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}