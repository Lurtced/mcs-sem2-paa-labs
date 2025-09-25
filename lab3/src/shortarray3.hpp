#pragma once

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <algorithm>



struct Storage {
    size_t capacity;
    short* data;
};

class ShortArray3 {
private:
    static const size_t inline_capacity = (sizeof(Storage) - sizeof(size_t)) / sizeof(short);

    union Data {
        short inline_data[inline_capacity];
        Storage storage;

        Data() {}
        ~Data() {}
    };

    struct SizeAndFlag {
        size_t count : 63;
        size_t is_inline : 1;
    };

    Data table;
    SizeAndFlag size_flag;

    short* data();
    const short* data() const;

public:
    ShortArray3();
    explicit ShortArray3(size_t initial_size, short fill_value = 0);
    ~ShortArray3();

    ShortArray3(const ShortArray3& other);
    ShortArray3& operator=(const ShortArray3& other);

    ShortArray3(ShortArray3&& other) noexcept;
    ShortArray3& operator=(ShortArray3&& other) noexcept;

    void push(short val);
    short pop();
    size_t size() const;
    size_t capacity() const;
    void resize(size_t new_size, short fill_value = 0);

    short& operator[](size_t index);
    const short& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const ShortArray3& arr);
};


void print_status(const ShortArray3& arr);