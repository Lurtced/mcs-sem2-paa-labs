#pragma once

#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int rows_;
    int cols_;
    double** data_;

public:
    Matrix(int n); // 1-matrix n x n
    Matrix(int m, int n, double fill_value = 0); // Matrix m x n filled with fill_value
    Matrix(const Matrix& other); // Copy constructor
    ~Matrix();

    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const;
    int get_width() const;
    void negate();
    void add_in_place(const Matrix& other);
    Matrix multiply(const Matrix& other) const;

    Matrix& operator=(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;
};
//ы
Matrix fibonacci_matrix(int n);

Matrix operator*(double scalar, const Matrix& matrix);
Matrix operator-(const Matrix& matrix);