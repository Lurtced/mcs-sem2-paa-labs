#pragma once

#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int rows_;
    int cols_;
    double** data_;

public:
    // Конструкторы
    Matrix(int n); // Единичная матрица n x n
    Matrix(int m, int n, double fill_value = 0); // Матрица m x n с заполнением fill_value
    Matrix(const Matrix& other); // Конструктор копирования
    ~Matrix(); // Деструктор

    // Методы
    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const;
    int get_width() const;
    void negate();
    void add_in_place(const Matrix& other);
    Matrix multiply(const Matrix& other) const;

    // Операторы
    Matrix& operator=(const Matrix& other); // Оператор присваивания
};

Matrix fibonacci_matrix(int n);