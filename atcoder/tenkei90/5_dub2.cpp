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

int K, B;
long long N;
int c[12];
mint dp[70][1002];
mint dp1[1002], dp2[1002];
int power10[65];  // power10[i] := 10^(2^i)

int main() {
  cin >> N >> B >> K;
  repeat(i, K) cin >> c[i];

  power10[0] = 10;
  repeat_from(i, 1, 65) power10[i] = power10[i - 1] * power10[i - 1] % B;

  // dp[i][j] := 2^i桁ある整数のうち、mod B がjの個数
  repeat(i, K) dp[0][c[i] % B] += 1;
  repeat(i, 64) {
    repeat(j, B) {
      repeat(k, B) {
        int nex = (j * power10[i] + k) % B;
        dp[i + 1][nex] += dp[i][j] * dp[i][k];
      }
    }
  }

  // for (int i = 0; i < 3; ++i) {
  //   cout << "i : " << i << endl;
  //   repeat(j, B) cout << dp[i][j] << " ";
  //   cout << endl;
  // }
  // cout << endl;

  mint *prev = dp1, *next = dp2;
  prev[0] = 1;

  // repeat(i, B) cout << prev[i] << " ";
  // cout << endl;

  int accum = 1;
  repeat(i, 64) {
    if ((N >> i) & 1) {
      repeat(j, B) next[j] = 0;

      repeat(j, B) repeat(k, B) {
        int nex = (j * accum + k) % B;
        next[nex] += dp[i][j] * prev[k];
      }

      // repeat(j, B) cout << next[j] << " ";
      // cout << endl;

      accum = accum * power10[i] % B;
      swap(prev, next);
    }
  }

  cout << prev[0] << endl;

  return 0;
}