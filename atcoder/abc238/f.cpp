#include <bits/stdc++.h>
using namespace std;

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

const int MOD = 998244353;
using mint = Fp<MOD>;

#define MAXN 300
mint dp1[MAXN + 2][MAXN + 2];
mint dp2[MAXN + 2][MAXN + 2];
int v[MAXN + 1], p[MAXN], q[MAXN];

int main() {
  int N, num;
  cin >> N >> num;
  for (int i = 0; i < N; ++i)
    cin >> p[i];
  for (int i = 0; i < N; ++i)
    cin >> q[i];
  for (int i = 0; i < N; ++i)
    v[p[i]] = q[i];

  // dp[j][k] :=
  // j個選んだ状態で、選ばなかった人物のうち、最も小さい順位がkである解きの通り数
  // 全員を選んでいる場合はk=N+1とした(無限の代わり)
  auto prev = dp1, next = dp2;
  prev[0][N + 1] = 1;
  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j <= num; ++j) {
      // initialize
      for (int k = 1; k <= N + 1; ++k)
        next[j][k] = 0;
      // if k < v[i]
      for (int k = 1; k < v[i]; ++k) {
        next[j][k] = prev[j][k];
      }
      // if k == v[i]
      next[j][v[i]] = 0;
      for (int p = v[i] + 1; p <= N + 1; ++p) {
        next[j][v[i]] += prev[j][p];
      }
      // if k > v[i]
      if (j > 0)
        for (int k = v[i] + 1; k <= N + 1; ++k) {
          next[j][k] = prev[j - 1][k];
        }
    }
    swap(prev, next);
  }
  mint ans = 0;
  for (int i = 1; i <= N + 1; ++i)
    ans += prev[num][i];
  cout << ans << endl;
  return 0;
}
