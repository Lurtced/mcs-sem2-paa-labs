#include "mystring.hpp"
#include <iostream>
#include <cstring>

MyString::MyString() : data(nullptr), length(0) { 
    // TODO☑: если строка пустая, то nullptr
}

MyString::MyString(const char* str) {
    length = std::strlen(str);
    if (length > 0) {
        data = new char[length + 1];
        std::strcpy(data, str);
    } else {
        data = nullptr;
    }
}

MyString::MyString(const MyString& other) : length(other.length) {
    if (length > 0) {
        data = new char[length + 1];
        std::strcpy(data, other.data);
    } else {
        data = nullptr;
    }
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        if (length > 0) {
            data = new char[length + 1];
            std::strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }
    return *this;
}

// Деструктор
MyString::~MyString() {
    delete[] data;
}

// Метод для получения i-того элемента строки
char MyString::get(int i) const {
    if (i < 0 || i >= static_cast<int>(length)) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

// Метод для установки i-того элемента строки
void MyString::set(int i, char c) {
    if (i < 0 || i >= static_cast<int>(length)) {
        throw std::out_of_range("Index out of range");
    }
    data[i] = c;
}

// Метод для замены текущего содержимого строки на новое
void MyString::set_new_string(const char* str) {
    delete[] data;
    length = std::strlen(str);
    if (length > 0) {
        data = new char[length + 1];
        std::strcpy(data, str);
    } else {
        data = nullptr;
    }
}

// Метод для вывода строки на консоль
void MyString::print() const {
    std::cout << data << std::endl;
}

// Метод для чтения строки с консоли
void MyString::read_line() {
    delete[] data;
    length = 0;
    data = nullptr;

    char buffer[256];
    std::cin.getline(buffer, 256);
    length = std::strlen(buffer);
    if (length > 0) {
        data = new char[length + 1];
        std::strcpy(data, buffer);
    }
}

// Метод для получения длины строки
std::size_t MyString::get_length() const {
    return length;
}