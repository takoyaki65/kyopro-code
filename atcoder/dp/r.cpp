#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
#define bit_stand(n, k) ((n >> k) & 1)
using namespace std;

template <class T>
inline int sz(T& x) {
  return x.size();
}

template <class T>
inline bool setmax(T& a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T& a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}

template <typename T, typename X>
auto vectors(T a, X x) {
  return vector<T>(x, a);
}

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
  auto cont = vectors(a, y, zs...);
  return vector<decltype(cont)>(x, cont);
}

template <int MOD>
struct Fp {
  long long val;
  constexpr Fp(long long v = 0) noexcept : val(v % MOD) {
    if (val < 0)
      val += MOD;
  }
  constexpr int getmod() { return MOD; }
  constexpr Fp operator-() const noexcept { return val ? MOD - val : 0; }
  constexpr Fp operator+(const Fp& r) const noexcept { return Fp(*this) += r; }
  constexpr Fp operator-(const Fp& r) const noexcept { return Fp(*this) -= r; }
  constexpr Fp operator*(const Fp& r) const noexcept { return Fp(*this) *= r; }
  constexpr Fp operator/(const Fp& r) const noexcept { return Fp(*this) /= r; }
  constexpr Fp& operator+=(const Fp& r) noexcept {
    val += r.val;
    if (val >= MOD)
      val -= MOD;
    return *this;
  }
  constexpr Fp& operator-=(const Fp& r) noexcept {
    val -= r.val;
    if (val < 0)
      val += MOD;
    return *this;
  }
  constexpr Fp& operator*=(const Fp& r) noexcept {
    val = val * r.val % MOD;
    return *this;
  }
  constexpr Fp& operator/=(const Fp& r) noexcept {
    // a * u + b * v  = 1 となるuを求める
    long long a = r.val, b = MOD, u = 1, v = 0;
    while (b) {
      long long t = a / b;
      a -= t * b;
      swap(a, b);
      u -= t * v;
      swap(u, v);
    }
    val = val * u % MOD;
    if (val < 0)
      val += MOD;
    return *this;
  }
  constexpr bool operator==(const Fp& r) const noexcept {
    return this->val == r.val;
  }
  constexpr bool operator!=(const Fp& r) const noexcept {
    return this->val != r.val;
  }
  friend constexpr ostream& operator<<(ostream& os, const Fp<MOD>& x) noexcept {
    return os << x.val;
  }
  friend constexpr Fp<MOD> modpow(const Fp<MOD>& a, long long n) noexcept {
    if (n == 0)
      return 1;
    auto t = modpow(a, n / 2);
    t = t * t;
    if (n & 1)
      t = t * a;
    return t;
  }
};

const int MOD = 1000000007;
using mint = Fp<MOD>;

template <typename T>
struct Matrix {
  const int row, col;
  vector<vector<T>> dat;

  Matrix(int _n, int _m) : row(_n), col(_m), dat(_n, vector<T>(_m)) {}

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

int main() {
  int N;
  long long K;
  cin >> N >> K;
  Matrix<mint> A(N, N);
  repeat(i, N) repeat(j, N) {
    int aij;
    cin >> aij;
    A(i, j) = aij;
  }

  Matrix<mint> P = eye<mint>(N);

  while (K > 0) {
    if (K & 1LL)
      P = P * A;
    A = A * A;
    K >>= 1LL;
  }

  mint ans = 0;
  repeat(i, N) repeat(j, N) ans += P(i, j);
  cout << ans << endl;
}