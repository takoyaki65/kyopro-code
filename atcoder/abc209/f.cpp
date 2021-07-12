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
#include <random>
#include <set>
#include <stack>
#include <unordered_map>
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

int N;
// dp[i][j] := 区間[1, i]の木を全て切り、
//               i番目の木がj番目に伐採されるようなものの総数
// H[i] < H[i+1]なら、(i+1)番目の木の後にi番目の木が切られなければならない
//  dp[i+1][j] = sum_{k=j}{i}dp[i][k]
// H[i] = H[i+1]なら、i番目の木はどの順番で切られていてもいい
//  dp[i+1][j] = sum_{k=1}{i}dp[i][k]
// H[i] > H[i+1]なら、
//  dp[i+1][j] = sum_{k=1}{j-1}dp[i][k]

// 初期値
// dp[1][1] = 1

// 目的値
// dp[N][1] + ... + dp[N][N]

mint dp[4020][4020];
mint acum[4020];
int H[4100];

int main() {
  cin >> N;
  repeat_from(i, 1, N + 1) cin >> H[i];

  dp[1][1] = 1;
  for (int i = 1; i < N; ++i) {
    acum[1] = dp[i][1];
    for (int j = 1; j < N; ++j)
      acum[j + 1] = acum[j] + dp[i][j + 1];
    if (H[i] < H[i + 1]) {
      // i番目の木は[j, j+1, ,,, i]番目に切られなければいけない
      for (int j = 1; j <= i; ++j) {
        dp[i + 1][j] = acum[i] - acum[j - 1];
      }
    } else if (H[i] > H[i + 1]) {
      // i番目の木は[1,2,...,j-1]番目に切られなければいけない
      for (int j = 2; j <= i + 1; ++j) {
        dp[i + 1][j] = acum[j - 1] - acum[0];
      }
    } else {
      // H[i] == H[i+1]
      // i番目の木は[1,2,...,i]番目に切られなければいけない
      for (int j = 1; j <= i + 1; ++j) {
        dp[i + 1][j] = acum[i] - acum[0];
      }
    }
  }

  mint ans = 0;
  for (int i = 1; i <= N; ++i)
    ans += dp[N][i];
  cout << ans << endl;

  return 0;
}