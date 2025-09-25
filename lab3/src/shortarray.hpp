#pragma once

#include <iostream>
#include <stdexcept>

class ShortArray {
private:
    short* data_;
    size_t capacity_;  // allocated memory
    size_t size_;      // current amount of elements

public:
    ShortArray();
    ShortArray(size_t initial_size, short fill_value = 0);

    ShortArray(const ShortArray& other);
    ShortArray& operator=(const ShortArray& other);

    ShortArray(ShortArray&& other) noexcept;
    ShortArray& operator=(ShortArray&& other) noexcept;

    ~ShortArray();

    void push(short new_val);
    short pop();
    size_t size() const;
    void resize(size_t new_size, short fill_value = 0);

    short& operator[](size_t index);
    const short& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const ShortArray& arr);
};