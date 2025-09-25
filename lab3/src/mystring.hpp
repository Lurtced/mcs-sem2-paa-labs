#pragma once

#include <iostream>
#include <cstring>

class MyString {
private:
    char* data_;
    std::size_t length_;

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();

    char get(int i) const;
    const char* get_data() const;
    void set(int i, char c);
    void set_new_string(const char* str);
    void print() const;
    void read_line();
    std::size_t get_length() const;

    MyString& operator=(const MyString& other);

    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* str);

    friend MyString operator+(const MyString& lhs, const MyString& rhs);
    friend MyString operator+(const MyString& lhs, const char* rhs);
    friend MyString operator+(const char* lhs, const MyString& rhs);

    MyString(MyString&& other) noexcept;
    MyString& operator=(MyString&& other) noexcept;

    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator<=(const MyString& other) const;
    bool operator>(const MyString& other) const;
    bool operator>=(const MyString& other) const;

    bool operator==(const char* str) const;
    bool operator!=(const char* str) const;
    bool operator<(const char* str) const;
    bool operator<=(const char* str) const;
    bool operator>(const char* str) const;
    bool operator>=(const char* str) const;

    char& operator[](int i);
    const char& operator[](int i) const;
};

bool operator==(const char* lhs, const MyString& rhs);
bool operator!=(const char* lhs, const MyString& rhs);
bool operator<(const char* lhs, const MyString& rhs);
bool operator<=(const char* lhs, const MyString& rhs);
bool operator>(const char* lhs, const MyString& rhs);
bool operator>=(const char* lhs, const MyString& rhs);
// ඞ imposter
std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);

MyString addTxtExtension(const MyString &path);