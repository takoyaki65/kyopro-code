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

vector<mint> polynomial_inverse(vector<mint> C, int L) {
  // (C[0] + C[1] * x + ... + C[N-1] * x^(N-1)) * P(x) == 1 (mod x^L)を満たす、
  // L-1 次以下の多項式 P(x) を計算量 O(N log N) で求める
  // 制約: C[0] == 1 でなければならない。
  int N = C.size();
  vector<mint> A = {1, 0};
  int level = 0;
  while ((1 << level) < L) {
    int CS = min(2 << level, N);
    vector<mint> P = convolution(A, vector<mint>(C.begin(), C.begin() + CS));
    assert(P.size() >= (2 << level));
    vector<mint> Q(2 << level);
    Q[0] = 1;
    for (int j = (1 << level); j < (2 << level); ++j) {
      Q[j] = -P[j];
    }
    A = convolution(A, Q);
    A.resize(4 << level);
    ++level;
  }
  A.resize(L);
  return A;
}

int main() {
  for (int i = 0; i <= 23; ++i) {
    fwdpow[i] = modpow(root, (MOD - 1) / (1 << i));
    // revpow[i] = 1 / fwdpow[i];
    revpow[i] = modpow(root, (MOD - 1) - (MOD - 1) / (1 << i));
  }
  int N, K;
  cin >> N >> K;
  vector<vector<mint>> dp(K + 1);
  dp[K] = {1, 1, 1};
  for (int i = K - 1; i >= 0; --i) {
    int limit = (i == 0 ? N : min(K / i, N));
    vector<mint> C(dp[i + 1].size());
    C[0] = 1;
    for (int j = 1; j < dp[i + 1].size(); ++j) {
      C[j] = -dp[i + 1][j];
    }
    vector<mint> G = polynomial_inverse(C, limit + 2);
    dp[i] = G;
  }
  cout << dp[0][N + 1] << endl;
  return 0;
}