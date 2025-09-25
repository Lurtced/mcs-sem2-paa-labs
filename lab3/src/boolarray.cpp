#include "boolarray.hpp"


size_t BoolArray::bytes_for_bits(size_t n) {
    return (n + 7) / 8;
}


BoolArray::BoolArray(size_t n)
    : size_(n), data_(new uint8_t[bytes_for_bits(n)]()) {
    std::memset(data_, 0, bytes_for_bits(n));
}


BoolArray::BoolArray(size_t n, bool value)
    : size_(n), data_(new uint8_t[bytes_for_bits(n)]()) {
    std::memset(data_, value ? 0xFF : 0x00, bytes_for_bits(n));
}


BoolArray::BoolArray(const BoolArray& other)
    : size_(other.size_), data_(new uint8_t[bytes_for_bits(size_)]) {
    std::memcpy(data_, other.data_, bytes_for_bits(size_));
}


BoolArray::~BoolArray() {
    delete[] data_;
}


BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        data_ = new uint8_t[bytes_for_bits(size_)];
        std::memcpy(data_, other.data_, bytes_for_bits(size_));
    }
    return *this;
}


BoolArray::Reference BoolArray::operator[](size_t index) {
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    return Reference(data_ + (index / 8), index % 8);
}

bool BoolArray::operator[](size_t index) const {
    if (index >= size_)
        throw std::out_of_range("Index out of range");

    uint8_t byte = data_[index / 8];
    return (byte >> (index % 8)) & 1;
}


size_t BoolArray::size() const {
    return size_;
}


void BoolArray::resize(size_t new_size, bool value) {
    size_t old_bytes = bytes_for_bits(size_);
    size_t new_bytes = bytes_for_bits(new_size);

    uint8_t* new_data = new uint8_t[new_bytes];
    // std::memset(new_data, value ? 0xFF : 0x00, new_bytes);

    size_t min_bytes = std::min(old_bytes, new_bytes);
    std::memcpy(new_data, data_, min_bytes);

    if (new_size > size_) {
        for (size_t i = size_; i < new_size; ++i) {
            size_t byte_index = i / 8;
            size_t bit_index = i % 8;
            if (value)
                new_data[byte_index] |= (1 << bit_index);
            else
                new_data[byte_index] &= ~(1 << bit_index);
        }
    }

    delete[] data_;
    data_ = new_data;
    size_ = new_size;
}

std::ostream& operator<<(std::ostream& os, const BoolArray& arr) {
    os << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) os << ", ";
        os << (arr[i] ? "true" : "false");
    }
    os << "]";
    return os;
}