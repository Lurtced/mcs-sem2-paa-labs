#pragma once

#include <iostream>
#include <cstdint>
#include <cstring>
#include <stdexcept>

class BoolArray {
private:
    size_t size_;
    uint8_t* data_;

    static size_t bytes_for_bits(size_t n);

public:
    class Reference {
    private:
        uint8_t* byte_;
        uint8_t bit_pos_;

    public:
        Reference(uint8_t* byte, uint8_t bit_pos)
            : byte_(byte), bit_pos_(bit_pos) {}

        operator bool() const {
            return (*byte_ >> bit_pos_) & 1;
        }

        Reference& operator=(bool value) {
            if (value)
                *byte_ |= (1 << bit_pos_);
            else
                *byte_ &= ~(1 << bit_pos_);
            return *this;
        }

        Reference& operator=(const Reference& other) {
            return this->operator=(static_cast<bool>(other));
        }
    };

    explicit BoolArray(size_t n);
    BoolArray(size_t n, bool value);

    BoolArray(const BoolArray& other);

    ~BoolArray();

    BoolArray& operator=(const BoolArray& other);

    Reference operator[](size_t index);
    bool operator[](size_t index) const;

    size_t size() const;

    void resize(size_t new_size, bool value = false);

    friend std::ostream& operator<<(std::ostream& os, const BoolArray& arr);
};