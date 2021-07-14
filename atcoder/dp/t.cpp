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

int N;
string S;

// dp[i][j] := 区間[1, i]までの数字を決めたときに、
//             決めた最後の数字A[i]より大きい数字が
//             j個残っているときの通り数
// dp[1][N-1] = dp[1][N-2] = ... = dp[1][0] = 1
// S[i-1] = '<'の場合
// A[1] ~ A[i-1]より大きい値の個数の候補は0 ~ N - (i-1)個あるので、
// dp[i][j] = dp[i-1][j+1] + dp[i-1][j+2] + ... + dp[i-1][N-i+1]
// S[i-1] = '>'の場合
// dp[i+1][j] = dp[i][0] + dp[i][1] + ... + dp[i][j]
mint dp[3002][3002];
mint acum[3002];

int main() {
  cin >> N >> S;
  for (int i = 0; i < N; ++i)
    dp[1][i] = 1;

  for (int i = 2; i <= N; ++i) {
    acum[0] = dp[i - 1][0];
    for (int j = 1; j <= N; ++j)
      acum[j] = acum[j - 1] + dp[i - 1][j];
    if (S[i - 2] == '<') {
      for (int j = 0; j <= N - i; ++j) {
        // for (int k = j + 1; k <= N - i + 1; ++k) {
        //   dp[i][j] += dp[i - 1][k];
        // }
        dp[i][j] = acum[N - i + 1] - acum[j];
      }
    } else {
      for (int j = 0; j <= N - i; ++j) {
        // for (int k = 0; k <= j; ++k) {
        //   dp[i][j] += dp[i - 1][k];
        // }
        dp[i][j] = acum[j];
      }
    }
  }

  cout << dp[N][0] << endl;
}