#include "matrix.hpp"

// Конструктор для единичной матрицы n x n
Matrix::Matrix(int n) : rows_(n), cols_(n) {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new double[cols_];
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

// Конструктор для матрицы m x n с заполнением fill_value
Matrix::Matrix(int m, int n, double fill_value) : rows_(m), cols_(n) {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new double[cols_];
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = fill_value;
        }
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new double[cols_];
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = other.data_[i][j];
        }
    }
}

// Деструктор
Matrix::~Matrix() {
    for (int i = 0; i < rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
}

// Оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // Освобождаем текущую память
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;

        // Копируем данные из другой матрицы
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

// Метод для получения значения элемента
double Matrix::get(int i, int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i][j];
}

// Метод для установки значения элемента
void Matrix::set(int i, int j, double value) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    data_[i][j] = value;
}

// Метод для получения высоты матрицы
int Matrix::get_height() const {
    return rows_;
}

// Метод для получения ширины матрицы
int Matrix::get_width() const {
    return cols_;
}

// Метод для операции -A
void Matrix::negate() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = -data_[i][j];
        }
    }
}

// Метод для операции this += other
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

// Метод для матричного умножения
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

    Matrix result(2, 2, 1); // Единичная матрица
    for (int i = 0; i < n; ++i) {
        result = result.multiply(base);
    }
    return result;
}