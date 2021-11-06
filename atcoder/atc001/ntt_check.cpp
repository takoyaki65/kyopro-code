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

// https://github.com/drken1215/algorithm/blob/master/MathCombinatorics/mod.cpp
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
  friend constexpr istream& operator>>(istream& is, Fp<MOD>& x) noexcept {
    long long v{};
    is >> v;
    x = Fp<MOD>(v);
    return is;
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

const int MOD = 998244353;
using mint = Fp<MOD>;

// 998244353の最小の原始根は3
// 998244353 = 119 * 2^23 + 1
// -> (3^119)^(2^23) = 1 (mod 998244353)
// -> (3^119)^i (i = 1,2,3,...,2^23)は2^23乗根
// また,
// -> (3^238)^(2^23) = 1 (mod 998244353)
// -> (3^238)^i (i = 1,2,3,...,2^22)は2^22乗根
// ....
// -> (3^998244352)^(2^0) = 1 (mod 998244353)
// -> (3^998244352)^i (i = 1) は1乗根
const mint root = 3;

// fwdpow[i] = 2^i乗根
// revpow[i] = fwdpow[i]^-1
mint fwdpow[32], revpow[32];

// 制約: Xのサイズは2のべき乗であること
void fourier_transform(vector<mint>& X, bool inv) {
  int N = X.size();
  int level = 0;
  vector<mint> Y(N);
  for (int i = N >> 1; i >= 1; i >>= 1) {
    ++level;
    mint p = (!inv ? fwdpow[level] : revpow[level]);
    mint mul = 1;
    for (int j = 0; 2 * j < N; j += i) {
      for (int k = 0; k < i; ++k) {
        mint g = mul * X[2 * j + k + i];
        Y[j + k] = X[2 * j + k] + g;
        Y[j + k + N / 2] = X[2 * j + k] - g;
      }
      mul *= p;
    }
    X = Y;
  }
}

void bit_reverse(vector<mint>& X) {
  const int n = X.size();
  // https://www.kurims.kyoto-u.ac.jp/~ooura/fftman/ftmn1_25.html
  int i = 0;
  for (int j = 1; j < n - 1; ++j) {
    // 変数iをビット逆順に加算する(0000 -> 1000 -> 0100 -> 1100 -> ....)
    for (int k = n >> 1; k > (i ^= k); k >>= 1)
      ;
    if (j < i) {
      swap(X[i], X[j]);
    }
  }
}

void fourier_transform2(vector<mint>& X, bool inv) {
  bit_reverse(X);
  const int n = X.size();
  const int lgn = __builtin_ctz(n);
  for (int s = 1; s <= lgn; ++s) {
    const int m = 1 << s;
    const mint wm = inv ? revpow[s] : fwdpow[s];
    for (int k = 0; k < n; k += m) {
      mint w = 1;
      for (int j = 0; j < m / 2; ++j) {
        auto t = w * X[k + j + m / 2];
        auto u = X[k + j];
        X[k + j] = u + t;
        X[k + j + m / 2] = u - t;
        w = w * wm;
      }
    }
  }
}

vector<mint> convolution(vector<mint> A, vector<mint> B) {
  // 多項式の積 A(x) * B(x) を計算量 O(n log n) で求める
  int L = A.size() + B.size() - 1;
  int sz = 2;
  while (sz < L)
    sz *= 2;

  A.resize(sz);
  fourier_transform(A, false);
  B.resize(sz);
  fourier_transform(B, false);
  for (int i = 0; i < sz; ++i) {
    A[i] = A[i] * B[i];
  }

  fourier_transform(A, true);
  A.resize(L);
  mint inv = mint(1) / sz;
  for (int i = 0; i < L; ++i) {
    A[i] *= inv;
  }
  return A;
}

int main() {
  for (int i = 0; i <= 23; ++i) {
    fwdpow[i] = modpow(root, (MOD - 1) / (1 << i));
    // revpow[i] = 1 / fwdpow[i];
    revpow[i] = modpow(root, (MOD - 1) - (MOD - 1) / (1 << i));
  }

  int N;
  cin >> N;
  if ((1 << __builtin_ctz(N)) != N) {
    cout << "error!" << endl;
    return 0;
  }

  vector<mint> A(N);
  for (int i = 0; i < N; ++i)
    cin >> A[i];

  auto B1 = A, B2 = A;
  fourier_transform(B1, false);
  fourier_transform2(B2, false);

  cout << "fourier_transform(by e869120)" << endl;
  for (int i = 0; i < N; ++i)
    cout << B1[i] << " ";
  cout << endl;
  cout << "fourier_transform(by algorithm-introduction)" << endl;
  for (int i = 0; i < N; ++i)
    cout << B2[i] << " ";
  cout << endl;

  return 0;
}