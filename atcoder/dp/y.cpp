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

template <class T>
struct BiCoef {
  vector<T> fact_, inv_, finv_;
  constexpr BiCoef() {}
  constexpr BiCoef(int n) noexcept : fact_(n, 1), inv_(n, 1), finv_(n, 1) {
    init(n);
  }
  constexpr void init(int n) noexcept {
    fact_.assign(n, 1), inv_.assign(n, 1), finv_.assign(n, 1);
    int MOD = fact_[0].getmod();
    for (int i = 2; i < n; ++i) {
      fact_[i] = fact_[i - 1] * i;
      inv_[i] = -inv_[MOD % i] * (MOD / i);
      finv_[i] = finv_[i - 1] * inv_[i];
    }
  }
  constexpr T com(int n, int k) const noexcept {
    if (n < k || n < 0 || k < 0)
      return 0;
    return fact_[n] * finv_[k] * finv_[n - k];
  }
  constexpr T fact(int n) const noexcept {
    if (n < 0)
      return 0;
    return fact_[n];
  }
  constexpr T inv(int n) const noexcept {
    if (n < 0)
      return 0;
    return inv_[n];
  }
  constexpr T finv(int n) const noexcept {
    if (n < 0)
      return 0;
    return finv_[n];
  }
};

const int MOD = 1000000007;
using mint = Fp<MOD>;

struct rc {
  int r, c;
  // 原点からのマンハッタン距離で比較
  bool operator<(const rc& rhs) const {
    return (r < rhs.r) || (r == rhs.r && c < rhs.c);
  }
};

int H, W, N;
rc vw[3010];

// dp[i] := 0~i-1番目の壁を避けてi番目の壁の位置にたどり着く場合の数
mint dp[3010];

int main() {
  cin >> H >> W >> N;
  repeat(i, N) cin >> vw[i].r >> vw[i].c;
  vw[N].r = H, vw[N].c = W;
  N += 1;
  sort(vw, vw + N);

  // cout << "rc: " << endl;
  // repeat(i, N) cout << vw[i].r << " " << vw[i].c << endl;

  BiCoef<mint> Cmb(H + W + 10);
  auto f = [&Cmb](int r, int l) -> mint { return Cmb.com(r + l, r); };
  for (int i = 0; i < N; ++i) {
    dp[i] = f(vw[i].r - 1, vw[i].c - 1);
    for (int j = 0; j < i; ++j) {
      int dx = vw[i].r - vw[j].r;
      int dy = vw[i].c - vw[j].c;
      if (dx >= 0 && dy >= 0) {
        dp[i] -= dp[j] * f(dx, dy);
      }
    }
  }

  // for (int i = 0; i < N; ++i) {
  //   cout << "dp[" << i << "] = " << dp[i] << endl;
  // }

  cout << dp[N - 1] << endl;

  return 0;
}