#include <algorithm>
#include <array>
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
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
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

char str[30][30];
int grid[30];
int H, W;

mint dp1[1 << 24], dp2[1 << 24];
bool ok[1 << 24];  // ok[bit] := 状態bitの置き方が(1段だけ見たとき)validか

int main() {
  cin >> H >> W;
  repeat(i, H) cin >> str[i];
  repeat(i, H) repeat(j, W) if (str[i][j] == '#') grid[i] += 1 << j;

  const int maxS = 1 << W;
  fill(ok, ok + maxS, true);
  repeat(i, maxS) {
    repeat(j, W - 1) {
      if ((i >> j) & 1 && (i >> (j + 1)) & 1) {
        ok[i] = false;
      }
      if (!ok[i])
        break;
    }
  }

  auto *prev = dp1, *next = dp2;
  prev[0] = 1;
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < maxS; ++j) {
      next[j] = 0;
      if (!ok[j])
        continue;
      if (j & grid[i])
        continue;
      for (int k = 0; k < maxS; ++k) {
        if (j & k || ((j >> 1) & k) || ((j << 1) & k))
          continue;
        next[j] += prev[k];
      }
    }
    swap(prev, next);
  }

  // for (int i = 0; i < maxS; ++i) {
  //   cout << "prev[" << i << "] = " << prev[i] << endl;
  // }

  mint ans = 0;
  for (int i = 0; i < maxS; ++i)
    ans += prev[i];
  cout << ans << endl;

  return 0;
}