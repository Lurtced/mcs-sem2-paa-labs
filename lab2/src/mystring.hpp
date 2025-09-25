#pragma once

#include <iostream>
#include <cstring>

class MyString {
private:
    char* data;
    std::size_t length;

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();
    MyString& operator=(const MyString& other);

    char get(int i) const;
    void set(int i, char c);
    void set_new_string(const char* str);
    void print() const;
    void read_line();
    std::size_t get_length() const; // Добавляем метод для получения длины строки
};