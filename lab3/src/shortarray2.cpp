#include "shortarray2.hpp"

ShortArray2::ShortArray2()
    : capacity_(BUILT_IN_CAPACITY), size_(0) {}

ShortArray2::ShortArray2(size_t initial_size, short fill_value)
    : size_(initial_size), capacity_(initial_size <= BUILT_IN_CAPACITY ? BUILT_IN_CAPACITY : initial_size) {
    if (capacity_ <= BUILT_IN_CAPACITY) {
        dynamic_data = nullptr;
        for (size_t i = 0; i < size_; ++i) {
            inline_data[i] = fill_value;
        }
    } else {
        dynamic_data = new short[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            dynamic_data[i] = fill_value;
        }
    }
}

ShortArray2::ShortArray2(const ShortArray2& other)
    : size_(other.size_), capacity_(other.capacity_) {
    if (other.using_inline()) {
        dynamic_data = nullptr;
        std::copy(other.inline_data, other.inline_data + size_, inline_data);
    } else {
        dynamic_data = new short[capacity_];
        std::copy(other.dynamic_data, other.dynamic_data + size_, dynamic_data);
    }
}

ShortArray2& ShortArray2::operator=(const ShortArray2& other) {
    if (this != &other) {
        if (!using_inline() && !other.using_inline()) {
            if (capacity_ < other.capacity_) {
                delete[] dynamic_data;
                capacity_ = other.capacity_;
                dynamic_data = new short[capacity_];
            }
        } else if (!using_inline() && other.using_inline()) {
            delete[] dynamic_data;
        } else if (using_inline() && !other.using_inline()) {
            dynamic_data = new short[other.capacity_];
        }

        size_ = other.size_;
        if (other.using_inline()) {
            std::copy(other.inline_data, other.inline_data + size_, inline_data);
        } else {
            std::copy(other.dynamic_data, other.dynamic_data + size_, dynamic_data);
        }
    }
    return *this;
}

ShortArray2::ShortArray2(ShortArray2&& other) noexcept
    : size_(other.size_), capacity_(other.capacity_) {
    if (other.using_inline()) {
        dynamic_data = nullptr;
        std::copy(other.inline_data, other.inline_data + size_, inline_data);
    } else {
        dynamic_data = other.dynamic_data;
        other.dynamic_data = nullptr;
    }
    other.size_ = 0;
    other.capacity_ = 0;
}

ShortArray2& ShortArray2::operator=(ShortArray2&& other) noexcept {
    if (this != &other) {
        if (!using_inline()) {
            delete[] dynamic_data;
        }

        size_ = other.size_;
        capacity_ = other.capacity_;
        if (other.using_inline()) {
            dynamic_data = nullptr;
            std::copy(other.inline_data, other.inline_data + size_, inline_data);
        } else {
            dynamic_data = other.dynamic_data;
            other.dynamic_data = nullptr;
        }

        other.size_ = other.capacity_ = 0;
    }
    return *this;
}

ShortArray2::~ShortArray2() {
    if (!using_inline()) {
        delete[] dynamic_data;
    }
}

void ShortArray2::push(short new_val) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        short* new_data = new short[new_capacity];

        std::copy(using_inline() ? inline_data : dynamic_data,
                  using_inline() ? inline_data + size_ : dynamic_data + size_,
                  new_data);

        if (!using_inline()) {
            delete[] dynamic_data;
        }

        dynamic_data = new_data;
        capacity_ = new_capacity;
    }

    (using_inline() ? inline_data[size_] : dynamic_data[size_]) = new_val;
    ++size_;
}

short ShortArray2::pop() {
    if (size_ == 0) {
        throw std::out_of_range("Cannot pop from an empty array");
    }
    --size_;
    return (using_inline() ? inline_data[size_] : dynamic_data[size_]);
}

size_t ShortArray2::size() const {
    return size_;
}

void ShortArray2::resize(size_t new_size, short fill_value) {
    if (new_size > capacity_) {
        short* new_data = new short[new_size];
        std::copy(using_inline() ? inline_data : dynamic_data,
                  using_inline() ? inline_data + size_ : dynamic_data + size_,
                  new_data);

        if (!using_inline()) {
            delete[] dynamic_data;
        }

        dynamic_data = new_data;
        capacity_ = new_size;
    }

    for (size_t i = size_; i < new_size; ++i) {
        (using_inline() ? inline_data[i] : dynamic_data[i]) = fill_value;
    }

    size_ = new_size;
}

short& ShortArray2::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return using_inline() ? inline_data[index] : dynamic_data[index];
}

const short& ShortArray2::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return using_inline() ? inline_data[index] : dynamic_data[index];
}

std::ostream& operator<<(std::ostream& os, const ShortArray2& arr) {
    os << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        os << arr[i];
        if (i != arr.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}