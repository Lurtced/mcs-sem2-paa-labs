#pragma once

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstddef>

class ShortArray2 {
private:
    static constexpr size_t BUILT_IN_CAPACITY = 8;
    union {
        short* dynamic_data;
        short inline_data[BUILT_IN_CAPACITY];
    };

    size_t capacity_;
    size_t size_;

    bool using_inline() const {
        return capacity_ <= BUILT_IN_CAPACITY;
    }

public:
    ShortArray2();
    ShortArray2(size_t initial_size, short fill_value = 0);

    ShortArray2(const ShortArray2& other);
    ShortArray2& operator=(const ShortArray2& other);

    ShortArray2(ShortArray2&& other) noexcept;
    ShortArray2& operator=(ShortArray2&& other) noexcept;

    ~ShortArray2();

    void push(short new_val);
    short pop();
    size_t size() const;
    void resize(size_t new_size, short fill_value = 0);

    short& operator[](size_t index);
    const short& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const ShortArray2& arr);
};