#pragma once
#include <stdexcept>
#include <iostream>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t Rows, size_t Columns>
class Matrix {
 public:
  T matrix_[Rows][Columns];
  size_t RowsNumber() const;
  size_t ColumnsNumber() const;
  T &operator()(size_t row, size_t column);
  const T &operator()(size_t row, size_t column) const;
  T &At(size_t row, size_t column);
  const T &At(size_t row, size_t column) const;
  Matrix<T, Rows, Columns> operator+(const Matrix<T, Rows, Columns> &matrix2) const;
  Matrix<T, Rows, Columns> operator-(const Matrix<T, Rows, Columns> &matrix2) const;
  Matrix<T, Rows, Columns> operator*(const int32_t &a) const;
  Matrix<T, Rows, Columns> operator/(const int32_t &a) const;
  Matrix<T, Rows, Columns> &operator+=(const Matrix<T, Rows, Columns> &matrix2);
  Matrix<T, Rows, Columns> &operator+=(const int32_t &a);
  Matrix<T, Rows, Columns> &operator-=(const Matrix<T, Rows, Columns> &matrix2);
  Matrix<T, Rows, Columns> &operator-=(const int32_t &a);
  Matrix<T, Rows, Columns> &operator*=(const int32_t &a);
  Matrix<T, Rows, Columns> &operator/=(const int32_t &a);
  bool operator==(const Matrix<T, Rows, Columns> &matrix2) const;
  bool operator!=(const Matrix<T, Rows, Columns> &matrix2) const;
  Matrix<T, Rows, Columns> &operator*=(const Matrix<T, Columns, Columns> &matrix2) {
    Matrix<T, Rows, Columns> result;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.matrix_[i][j] = 0;
        for (size_t k = 0; k < Columns; ++k) {
          result.matrix_[i][j] += matrix_[i][k] * matrix2.matrix_[k][j];
        }
      }
    }
    *this = result;
    return *this;
  }
};

template <class T, size_t Rows, size_t Columns>
size_t Matrix<T, Rows, Columns>::RowsNumber() const {
  return Rows;
}

template <class T, size_t Rows, size_t Columns>
size_t Matrix<T, Rows, Columns>::ColumnsNumber() const {
  return Columns;
}

template <class T, size_t Rows, size_t Columns>
T &Matrix<T, Rows, Columns>::operator()(size_t row, size_t column) {
  return matrix_[row][column];
}

template <class T, size_t Rows, size_t Columns>
const T &Matrix<T, Rows, Columns>::operator()(size_t row, size_t column) const {
  return matrix_[row][column];
}

template <class T, size_t Rows, size_t Columns>
T &Matrix<T, Rows, Columns>::At(size_t row, size_t column) {
  if (row >= Rows || column >= Columns) {
    throw MatrixOutOfRange();
  }
  return matrix_[row][column];
}

template <class T, size_t Rows, size_t Columns>
const T &Matrix<T, Rows, Columns>::At(size_t row, size_t column) const {
  if (row >= Rows || column >= Columns) {
    throw MatrixOutOfRange();
  }
  return matrix_[row][column];
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Columns, Rows> GetTransposed(Matrix<T, Rows, Columns> &matrix) {
  Matrix<T, Columns, Rows> ret;
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      ret.matrix_[j][i] = matrix.matrix_[i][j];
    }
  }
  return ret;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator+(const Matrix<T, Rows, Columns> &matrix2) const {
  Matrix<T, Rows, Columns> ret;
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      ret.matrix_[i][j] = matrix_[i][j] + matrix2.matrix_[i][j];
    }
  }
  return ret;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator-(const Matrix<T, Rows, Columns> &matrix2) const {
  Matrix<T, Rows, Columns> ret;
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      ret.matrix_[i][j] = matrix_[i][j] - matrix2.matrix_[i][j];
    }
  }
  return ret;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator*(const int32_t &a) const {
  Matrix<T, Rows, Columns> ret;
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      ret.matrix_[i][j] = matrix_[i][j] * a;
    }
  }
  return ret;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> &Matrix<T, Rows, Columns>::operator+=(const Matrix<T, Rows, Columns> &matrix2) {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      matrix_[i][j] += matrix2.matrix_[i][j];
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> &Matrix<T, Rows, Columns>::operator-=(const Matrix<T, Rows, Columns> &matrix2) {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      matrix_[i][j] -= matrix2.matrix_[i][j];
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> &Matrix<T, Rows, Columns>::operator+=(const int32_t &a) {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      matrix_[i][j] += a;
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> &Matrix<T, Rows, Columns>::operator-=(const int32_t &a) {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      matrix_[i][j] -= a;
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> &Matrix<T, Rows, Columns>::operator*=(const int32_t &a) {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      matrix_[i][j] *= a;
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> &Matrix<T, Rows, Columns>::operator/=(const int32_t &a) {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      matrix_[i][j] /= a;
    }
  }
  return *this;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator/(const int32_t &a) const {
  Matrix<T, Rows, Columns> ret;
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      ret.matrix_[i][j] = matrix_[i][j] / a;
    }
  }
  return ret;
}

template <class T, size_t Rows, size_t Columns>
bool Matrix<T, Rows, Columns>::operator==(const Matrix<T, Rows, Columns> &matrix2) const {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      if (matrix_[i][j] != matrix2.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template <class T, size_t Rows, size_t Columns>
bool Matrix<T, Rows, Columns>::operator!=(const Matrix<T, Rows, Columns> &matrix2) const {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      if (matrix_[i][j] != matrix2.matrix_[i][j]) {
        return true;
      }
    }
  }
  return false;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator*(const int32_t &a, const Matrix<T, Rows, Columns> &matrix2) {
  Matrix<T, Rows, Columns> ret;
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Columns; j++) {
      ret.matrix_[i][j] = matrix2.matrix_[i][j] * a;
    }
  }
  return ret;
}

template <class T, size_t Rows1, size_t Columns1, size_t Columns2>
Matrix<T, Rows1, Columns2> operator*(const Matrix<T, Rows1, Columns1> &matrix1,
                                     const Matrix<T, Columns1, Columns2> &matrix2) {
  Matrix<T, Rows1, Columns2> ret;
  for (size_t i = 0; i < Rows1; i++) {
    for (size_t j = 0; j < Columns2; j++) {
      T s = 0;
      for (size_t k = 0; k < Columns1; k++) {
        s += matrix1.matrix_[i][k] * matrix2.matrix_[k][j];
      }
      ret.matrix_[i][j] = s;
    }
  }
  return ret;
}

template <class T, size_t Rows, size_t Columns>
std::istream &operator>>(std::istream &is, Matrix<T, Rows, Columns> &matrix) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      is >> matrix.matrix_[i][j];
    }
  }
  return is;
}

template <class T, size_t Rows, size_t Columns>
std::ostream &operator<<(std::ostream &os, const Matrix<T, Rows, Columns> &matrix) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      if (j != Columns - 1) {
        os << matrix.matrix_[i][j] << ' ';
      } else {
        os << matrix.matrix_[i][j];
      }
    }
    os << '\n';
  }
  return os;
}
