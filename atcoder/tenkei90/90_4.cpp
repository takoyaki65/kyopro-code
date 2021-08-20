#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

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

int main() {
  int N, K;
  cin >> N >> K;
  auto dp = vectors(mint(0), K + 2, N + 1, N + 1);
  // dp[h][l][r]: 配列の区間(A[l],A[l+1], ...,A[r-1])で、
  // すべて A[i] >= hであるものの個数
  for (int h = K + 1; h >= 0; --h) {
    for (int i = 0; i <= N; ++i) {
      dp[h][i][i] = 1;
    }
  }

  for (int h = K; h >= 0; --h) {
    for (int w = 1; w <= N; ++w) {
      for (int l = 0; l + w <= N; ++l) {
        int r = l + w;
        if (h * (r - l) > K)
          continue;

        assert(h + 1 <= K + 1);
        dp[h][l][r] += dp[h + 1][l][r];
        // A[l], ...,A[i-1]がh以上(全てhより大きいこともある)で、
        // A[i]=hであり、
        // A[i+1], ...,A[r-1]がh+1以上である場合
        for (int i = r - 1; i >= l; --i) {
          dp[h][l][r] += dp[h][l][i] * dp[h + 1][i + 1][r];
        }
      }
    }
  }

  cout << dp[0][0][N] << endl;
  return 0;
}