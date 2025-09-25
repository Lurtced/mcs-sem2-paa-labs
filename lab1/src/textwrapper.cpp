#include "textwrapper.hpp"
#include <iostream>
#include <cctype>

// Конструктор
TextWrapper::TextWrapper(const MyString& input, int width)
    : text(input), line_width(width), current_pos(0), current_line_length(0) {}

// Метод для проверки конца текста
bool TextWrapper::is_end_of_text() const {
    return current_pos >= text.get_length();
}

// Метод для проверки конца строки
bool TextWrapper::is_end_of_line() const {
    return current_line_length >= line_width;
}

// Метод для вывода текущей строки
void TextWrapper::print_current_line() const {
    for (int i = current_pos - current_line_length; i < current_pos; ++i) {
        std::cout << text.get(i);
    }
    std::cout << std::endl;
}

// Метод для перехода к следующему слову
void TextWrapper::advance_to_next_word() {
    while (current_pos < text.get_length() && !std::isspace(text.get(current_pos))) {
        ++current_pos;
        ++current_line_length;
        if (is_end_of_line()) {
            print_current_line();
            current_line_length = 0;
        }
    }
    while (current_pos < static_cast<int>(text.get_length()) && std::isspace(text.get(current_pos))) {
        ++current_pos;
    }
}

// Метод для вывода текста с переносами
void TextWrapper::print_wrapped() {
    while (!is_end_of_text()) {
        advance_to_next_word();
        if (is_end_of_line()) {
            print_current_line();
            current_line_length = 0;
        }
    }
    if (current_line_length > 0) {
        print_current_line();
    }
}