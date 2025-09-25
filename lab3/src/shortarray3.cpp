#include "shortarray3.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>


short* ShortArray3::data() {
    return size_flag.is_inline ? table.inline_data : table.storage.data;
}

const short* ShortArray3::data() const {
    return size_flag.is_inline ? table.inline_data : table.storage.data;
}


ShortArray3::ShortArray3()
    : size_flag{0, true} {
    std::fill(table.inline_data, table.inline_data + inline_capacity, 0);
    table.storage.capacity = inline_capacity;
}

ShortArray3::ShortArray3(size_t initial_size, short fill_value)
    : size_flag{initial_size, initial_size <= inline_capacity} {

    if (size_flag.is_inline) {
        std::fill(table.inline_data, table.inline_data + inline_capacity, 0);
        std::fill(table.inline_data, table.inline_data + initial_size, fill_value);
        table.storage.capacity = inline_capacity;
    } else {
        table.storage.capacity = initial_size;
        table.storage.data = new short[initial_size];
        std::fill(table.storage.data, table.storage.data + initial_size, fill_value);
    }
}


ShortArray3::~ShortArray3() {
    if (!size_flag.is_inline) {
        delete[] table.storage.data;
    }
}


ShortArray3::ShortArray3(const ShortArray3& other)
    : size_flag(other.size_flag) {

    if (size_flag.is_inline) {
        std::copy(other.table.inline_data,
                  other.table.inline_data + other.size_flag.count,
                  table.inline_data);
        table.storage.capacity = inline_capacity;
    } else {
        table.storage.capacity = other.table.storage.capacity;
        table.storage.data = new short[table.storage.capacity];
        std::copy(other.table.storage.data,
                  other.table.storage.data + other.size_flag.count,
                  table.storage.data);
    }
}

ShortArray3& ShortArray3::operator=(const ShortArray3& other) {
    if (this != &other) {
        if (!size_flag.is_inline && !other.size_flag.is_inline) {
            delete[] table.storage.data;
        }

        size_flag = other.size_flag;

        if (size_flag.is_inline) {
            std::copy(other.table.inline_data,
                      other.table.inline_data + other.size_flag.count,
                      table.inline_data);
            table.storage.capacity = inline_capacity;
        } else {
            table.storage.capacity = other.table.storage.capacity;
            table.storage.data = new short[table.storage.capacity];
            std::copy(other.table.storage.data,
                      other.table.storage.data + other.size_flag.count,
                      table.storage.data);
        }
    }
    return *this;
}


ShortArray3::ShortArray3(ShortArray3&& other) noexcept
    : size_flag(other.size_flag) {

    if (size_flag.is_inline) {
        std::copy(other.table.inline_data,
                  other.table.inline_data + other.size_flag.count,
                  table.inline_data);
        table.storage.capacity = inline_capacity;
    } else {
        table.storage = other.table.storage;
        other.table.storage.data = nullptr;
        other.size_flag = {0, true};
    }
}

ShortArray3& ShortArray3::operator=(ShortArray3&& other) noexcept {
    if (this != &other) {
        if (!size_flag.is_inline) {
            delete[] table.storage.data;
        }

        size_flag = other.size_flag;

        if (size_flag.is_inline) {
            std::copy(other.table.inline_data,
                      other.table.inline_data + other.size_flag.count,
                      table.inline_data);
            table.storage.capacity = inline_capacity;
        } else {
            table.storage = other.table.storage;
            other.table.storage.data = nullptr;
            other.size_flag = {0, true};
        }
    }
    return *this;
}


void ShortArray3::push(short val) {
    if (size_flag.count == (size_flag.is_inline ? inline_capacity : table.storage.capacity)) {
        size_t new_cap = size_flag.is_inline ? 8 : table.storage.capacity * 2;
        short* new_data = new short[new_cap];

        for (size_t i = 0; i < size_flag.count; ++i) {
            new_data[i] = data()[i];
        }

        if (!size_flag.is_inline) {
            delete[] table.storage.data;
        }

        table.storage.data = new_data;
        table.storage.capacity = new_cap;
        size_flag.is_inline = false;
    }

    data()[size_flag.count++] = val;
}

short ShortArray3::pop() {
    if (size_flag.count == 0) {
        throw std::out_of_range("Cannot pop from empty array");
    }
    return data()[--size_flag.count];
}

void ShortArray3::resize(size_t new_size, short fill_value) {
    if (new_size > capacity()) {
        short* new_data = new short[new_size];

        for (size_t i = 0; i < size_flag.count; ++i) {
            new_data[i] = data()[i];
        }

        for (size_t i = size_flag.count; i < new_size; ++i) {
            new_data[i] = fill_value;
        }

        if (!size_flag.is_inline) {
            delete[] table.storage.data;
        }

        if (new_size <= inline_capacity) {
            std::copy(new_data, new_data + new_size, table.inline_data);
            table.storage.capacity = inline_capacity;
            size_flag.is_inline = true;
        } else {
            table.storage.data = new_data;
            table.storage.capacity = new_size;
            size_flag.is_inline = false;
        }
    }

    size_flag.count = new_size;
}


size_t ShortArray3::size() const {
    return size_flag.count;
}

size_t ShortArray3::capacity() const {
    return size_flag.is_inline ? inline_capacity : table.storage.capacity;
}


short& ShortArray3::operator[](size_t idx) {
    if (idx >= size_flag.count) {
        throw std::out_of_range("Index out of range");
    }
    return data()[idx];
}

const short& ShortArray3::operator[](size_t idx) const {
    if (idx >= size_flag.count) {
        throw std::out_of_range("Index out of range");
    }
    return data()[idx];
}


std::ostream& operator<<(std::ostream& os, const ShortArray3& arr) {
    os << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        os << static_cast<int>(arr[i]);
        if (i != arr.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}


void print_status(const ShortArray3& arr) {
    std::cout << "Array: " << arr << "\n";
    std::cout << "Size: " << arr.size() << ", Capacity: " << arr.capacity() << "\n";
    std::cout << "--------------------\n";
}