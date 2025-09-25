#include "mystring.hpp"
#include <iostream>
#include <cstring>

MyString::MyString() : data_(nullptr), length_(0) { }

MyString::MyString(const char* str) {
    length_ = std::strlen(str);
    if (length_ > 0) {
        data_ = new char[length_ + 1];
        std::strcpy(data_, str);
    } else {
        data_ = nullptr;
    }
}

MyString::MyString(const MyString& other) : length_(other.length_) {
    if (length_ > 0) {
        data_ = new char[length_ + 1];
        std::strcpy(data_, other.data_);
    } else {
        data_ = nullptr;
    }
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data_;
        length_ = other.length_;
        if (length_ > 0) {
            data_ = new char[length_ + 1];
            std::strcpy(data_, other.data_);
        } else {
            data_ = nullptr;
        }
    }
    return *this;
}


MyString::~MyString() {
    delete[] data_;
}


char MyString::get(int i) const {
    if (i < 0 || i >= static_cast<int>(length_)) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i];
}


const char* MyString::get_data() const {
    return data_;
}


void MyString::set(int i, char c) {
    if (i < 0 || i >= static_cast<int>(length_)) {
        throw std::out_of_range("Index out of range");
    }
    data_[i] = c;
}


void MyString::set_new_string(const char* str) {
    delete[] data_;
    length_ = std::strlen(str);
    if (length_ > 0) {
        data_ = new char[length_ + 1];
        std::strcpy(data_, str);
    } else {
        data_ = nullptr;
    }
}


void MyString::print() const {
    if (data_) {
        std::cout << data_ << std::endl;
    } else {
        std::cout << "(empty)" << std::endl;
    }
}


void MyString::read_line() {
    delete[] data_;
    length_ = 0;
    data_ = nullptr;

    char buffer[256];
    std::cin.getline(buffer, 256);
    length_ = std::strlen(buffer);
    if (length_ > 0) {
        data_ = new char[length_ + 1];
        std::strcpy(data_, buffer);
    }
}


std::size_t MyString::get_length() const {
    return length_;
}


MyString& MyString::operator+=(const MyString& other) {
    std::size_t new_len = length_ + other.length_;

    if (new_len == 0) {
        delete[] data_;
        data_ = nullptr;
        length_ = 0;
        return *this;
    }

    char* new_data = new char[new_len + 1];

    if (data_) {
        std::strcpy(new_data, data_);
    }

    if (other.data_) {
        std::strcpy(new_data + length_, other.data_);
    }

    delete[] data_;
    data_ = new_data;
    length_ = new_len;

    return *this;
}


MyString& MyString::operator+=(const char* str) {
    std::size_t other_len = std::strlen(str);
    char* new_data = new char[length_ + other_len + 1];
    std::strcpy(new_data, data_);
    std::strcpy(new_data + length_, str);

    delete[] data_;
    data_ = new_data;
    length_ += other_len;
    return *this;
}


MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString result;
    result.length_ = lhs.length_ + rhs.length_;
    result.data_ = new char[result.length_ + 1];
    std::strcpy(result.data_, lhs.data_);
    std::strcpy(result.data_ + lhs.length_, rhs.data_);
    return result;
}


MyString operator+(const MyString& lhs, const char* rhs) {
    std::size_t other_len = std::strlen(rhs);
    MyString result;
    result.length_ = lhs.length_ + other_len;
    result.data_ = new char[result.length_ + 1];
    std::strcpy(result.data_, lhs.data_);
    std::strcpy(result.data_ + lhs.length_, rhs);
    return result;
}


MyString operator+(const char* lhs, const MyString& rhs) {
    std::size_t other_len = std::strlen(lhs);
    MyString result;
    result.length_ = other_len + rhs.length_;
    result.data_ = new char[result.length_ + 1];
    std::strcpy(result.data_, lhs);
    std::strcpy(result.data_ + other_len, rhs.data_);
    return result;
}


MyString::MyString(MyString&& other) noexcept
    : data_(other.data_), length_(other.length_) {
    other.data_ = nullptr;
    other.length_ = 0;
}


MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        length_ = other.length_;

        other.data_ = nullptr;
        other.length_ = 0;
    }
    return *this;
}


bool MyString::operator==(const MyString& other) const {
    return std::strcmp(data_ ? data_ : "", other.data_ ? other.data_ : "") == 0;
}


bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}


bool MyString::operator<(const MyString& other) const {
    return std::strcmp(data_ ? data_ : "", other.data_ ? other.data_ : "") < 0;
}


bool MyString::operator<=(const MyString& other) const {
    return std::strcmp(data_ ? data_ : "", other.data_ ? other.data_ : "") <= 0;
}


bool MyString::operator>(const MyString& other) const {
    return other < *this;
}


bool MyString::operator>=(const MyString& other) const {
    return other <= *this;
}


bool MyString::operator==(const char* str) const {
    return std::strcmp(data_ ? data_ : "", str ? str : "") == 0;
}


bool MyString::operator!=(const char* str) const {
    return !(*this == str);
}


bool MyString::operator<(const char* str) const {
    return std::strcmp(data_ ? data_ : "", str ? str : "") < 0;
}


bool MyString::operator<=(const char* str) const {
    return std::strcmp(data_ ? data_ : "", str ? str : "") <= 0;
}


bool MyString::operator>(const char* str) const {
    return std::strcmp(data_ ? data_ : "", str ? str : "") > 0;
}


bool MyString::operator>=(const char* str) const {
    return std::strcmp(data_ ? data_ : "", str ? str : "") >= 0;
}


bool operator==(const char* lhs, const MyString& rhs) {
    return rhs == lhs;
}


bool operator!=(const char* lhs, const MyString& rhs) {
    return !(lhs == rhs);
}


bool operator<(const char* lhs, const MyString& rhs) {
    return std::strcmp(lhs ? lhs : "", rhs.get_data() ? rhs.get_data() : "") < 0;
}


bool operator<=(const char* lhs, const MyString& rhs) {
    return std::strcmp(lhs ? lhs : "", rhs.get_data() ? rhs.get_data() : "") <= 0;
}


bool operator>(const char* lhs, const MyString& rhs) {
    return rhs < lhs;
}


bool operator>=(const char* lhs, const MyString& rhs) {
    return rhs <= lhs;
}


char& MyString::operator[](int i) {
    if (i < 0 || i >= static_cast<int>(length_)) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i];
}

const char& MyString::operator[](int i) const {
    if (i < 0 || i >= static_cast<int>(length_)) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i];
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    if (str.get_data()) {
        os << str.get_data();
    }
    return os;
}


std::istream& operator>>(std::istream& is, MyString& str) {
    const int bufferSize = 256;
    char buffer[bufferSize];

    is.getline(buffer, bufferSize);

    str.set_new_string(buffer);
    return is;
}

MyString addTxtExtension(const MyString &path);