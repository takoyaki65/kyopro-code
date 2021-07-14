#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Matrix {
  const int row, col;
  vector<vector<T>> dat;

  Matrix(int _n, int _m) : row(_n), col(_m), dat(_n, vector<T>(_m)) {}

  Matrix(const Matrix& rhs) : row(rhs.row), col(rhs.col), dat(rhs.dat) {}

  Matrix& operator=(const Matrix& rhs) {
    if (this->col != rhs.col || this->row != rhs.row) {
      cout << "invalid matrix substitution" << endl;
      assert(true);
    }
    this->dat = rhs.dat;
    return *this;
  }

  T& operator()(int i, int j) { return dat[i][j]; }
  T operator()(int i, int j) const { return dat[i][j]; }

  Matrix operator*(const Matrix& rhs) const {
    if (this->col != rhs.row) {
      cout << "invalid matrix mul operation: col != lhs.row" << endl;
      assert(true);
    }
    Matrix ret(this->row, rhs.col);
    for (int i = 0; i < ret.row; ++i) {
      for (int j = 0; j < ret.col; ++j) {
        for (int k = 0; k < this->col; ++k) {
          ret(i, j) += (*this)(i, k) * rhs(k, j);
        }
      }
    }
    return ret;
  }
};

template <typename T>
Matrix<T> eye(int n) {
  Matrix<T> ret(n, n);
  repeat(i, n) ret(i, i) = 1;
  return ret;
}
