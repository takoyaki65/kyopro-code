#include <bits/stdc++.h>
using namespace std;

long long MOD = 1000000007;
struct mint {
  long long val;
  mint(long long v = 0) noexcept : val(v % MOD) {
    if (val < 0)
      val += MOD;
  }
  mint operator-() const noexcept { return val ? MOD - val : 0; }
  mint operator+(const mint& r) const noexcept { return mint(*this) += r; }
  mint operator-(const mint& r) const noexcept { return mint(*this) -= r; }
  mint operator*(const mint& r) const noexcept { return mint(*this) *= r; }
  mint& operator+=(const mint& r) noexcept {
    val += r.val;
    if (val >= MOD)
      val -= MOD;
    return *this;
  }
  mint& operator-=(const mint& r) noexcept {
    val -= r.val;
    if (val < 0)
      val += MOD;
    return *this;
  }
  mint& operator*=(const mint& r) noexcept {
    val = val * r.val % MOD;
    return *this;
  }
  bool operator==(const mint& r) const noexcept { return this->val == r.val; }
  bool operator!=(const mint& r) const noexcept { return this->val != r.val; }
  friend ostream& operator<<(ostream& os, const mint& x) noexcept {
    return os << x.val;
  }
  friend mint modpow(const mint& a, long long n) noexcept {
    if (n == 0)
      return 1;
    auto t = modpow(a, n / 2);
    t = t * t;
    if (n & 1)
      t = t * a;
    return t;
  }
};
