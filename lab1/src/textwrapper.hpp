#pragma once

#include "mystring.hpp"

class TextWrapper {
private:
    MyString text;
    int line_width;
    int current_pos;
    int current_line_length;

    bool is_end_of_text() const;
    bool is_end_of_line() const;
    void print_current_line() const;
    void advance_to_next_word();

public:
    TextWrapper(const MyString& input, int width);
    // TODO☑: уберите const с метода и хаки const_cast-ом
    void print_wrapped();
};