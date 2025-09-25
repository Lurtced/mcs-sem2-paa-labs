#include "matrix.hpp"


Matrix::Matrix(int n) : rows_(n), cols_(n) {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new double[cols_];
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}


Matrix::Matrix(int m, int n, double fill_value) : rows_(m), cols_(n) {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new double[cols_];
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = fill_value;
        }
    }
}


Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new double[cols_];
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = other.data_[i][j];
        }
    }
}


Matrix::~Matrix() {
    for (int i = 0; i < rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
}


Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;

        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = new double*[rows_];
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new double[cols_];
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] = other.data_[i][j];
            }
        }
    }
    return *this;
}


double Matrix::get(int i, int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i][j];
}


void Matrix::set(int i, int j, double value) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    data_[i][j] = value;
}


int Matrix::get_height() const {
    return rows_;
}


int Matrix::get_width() const {
    return cols_;
}


void Matrix::negate() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = -data_[i][j];
        }
    }
}


void Matrix::add_in_place(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Incompatible matrix sizes for addition");
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] += other.data_[i][j];
        }
    }
}


Matrix Matrix::multiply(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Incompatible matrix sizes for multiplication");
    }
    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            double sum = 0.0;
            for (int k = 0; k < cols_; ++k) {
                sum += data_[i][k] * other.data_[k][j];
            }
            result.set(i, j, sum);
        }
    }
    return result;
}

// fibonacci :)
Matrix fibonacci_matrix(int n) {
    Matrix base(2, 2);
    base.set(0, 0, 1);
    base.set(0, 1, 1);
    base.set(1, 0, 1);
    base.set(1, 1, 0);

    Matrix result(2, 2, 1);
    for (int i = 0; i < n; ++i) {
        result = result.multiply(base);
    }
    return result;
}



Matrix& Matrix::operator+=(const Matrix& other) {
    add_in_place(other);
    return *this;
}


Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Incompatible matrix sizes for subtraction");
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] -= other.data_[i][j];
        }
    }
    return *this;
}


Matrix& Matrix::operator*=(double scalar) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] *= scalar;
        }
    }
    return *this;
}


Matrix& Matrix::operator/=(double scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero");
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] /= scalar;
        }
    }
    return *this;
}


Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(*this);
    result += other;
    return result;
}


Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(*this);
    result -= other;
    return result;
}


Matrix Matrix::operator*(const Matrix& other) const {
    return multiply(other);
}


Matrix Matrix::operator*(double scalar) const {
    Matrix result(*this);
    result *= scalar;
    return result;
}


Matrix Matrix::operator/(double scalar) const {
    Matrix result(*this);
    result /= scalar;
    return result;
}


Matrix operator*(double scalar, const Matrix& matrix) {
    return matrix * scalar;
}


Matrix operator-(const Matrix& matrix) {
    Matrix result(matrix);
    result.negate();
    return result;
}


Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
}


Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;

        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = other.data_;

        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}