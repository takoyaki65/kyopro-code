#include <bits/stdc++.h>
using namespace std;

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

const unsigned long long pow10[] = {1uLL,
                                    10uLL,
                                    100uLL,
                                    1000uLL,
                                    10000uLL,
                                    100000uLL,
                                    1000000uLL,
                                    10000000uLL,
                                    100000000uLL,
                                    1000000000uLL,
                                    10000000000uLL,
                                    100000000000uLL,
                                    1000000000000uLL,
                                    10000000000000uLL,
                                    100000000000000uLL,
                                    1000000000000000uLL,
                                    10000000000000000uLL,
                                    100000000000000000uLL,
                                    1000000000000000000uLL,
                                    10000000000000000000uLL};

mint f(unsigned long long N) {
  return mint(N) * mint(N + 1) / 2;
}

int main() {
  unsigned long long L, R;
  cin >> L >> R;

  mint ans = 0;

  for (int i = 1; i <= 19; ++i) {
    // [pow10[i-1], pow10[i])
    unsigned long long low = pow10[i - 1];
    unsigned long long high = pow10[i] - 1uLL;
    if (L <= high && low <= R) {
      ans += (f(min(high, R)) - f(max(low, L) - 1)) * i;
    }
  }

  cout << ans << endl;

  return 0;
}