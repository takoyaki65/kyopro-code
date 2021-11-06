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

template <int MOD, int ROOT>
struct NTT {
  using mint = Fp<MOD>;

  // fwdpow[i] := 2^i乗根
  mint fwdpow[32], invpow[32];

  NTT() {
    int lg = __builtin_ctz(MOD - 1);
    // cout << "lg: " << lg << endl;
    for (int i = 0; i <= lg; ++i) {
      fwdpow[i] = modpow(mint(ROOT), (MOD - 1) / (1 << i));
      invpow[i] = modpow(mint(ROOT), (MOD - 1) - (MOD - 1) / (1 << i));
    }
  }

  vector<mint> bit_reverser_copy(const vector<mint>& a) {
    const int n = a.size();
    vector<mint> A = a;
    // https://www.kurims.kyoto-u.ac.jp/~ooura/fftman/ftmn1_25.html
    int i = 0;
    for (int j = 1; j < n - 1; ++j) {
      // 変数iをビット逆順に加算する(0000 -> 1000 -> 0100 -> 1100 -> ....)
      for (int k = n >> 1; k > (i ^= k); k >>= 1)
        ;
      if (j < i) {
        swap(A[i], A[j]);
      }
    }
    return A;
  }

  // number-theoretic-transform
  vector<mint> trans(const vector<mint>& a, int lgn, bool inv) {
    auto A = bit_reverser_copy(a);
    const int n = a.size();
    for (int s = 1; s <= lgn; ++s) {
      const int m = 1 << s;
      const mint wm = inv ? invpow[s] : fwdpow[s];
      for (int k = 0; k < n; k += m) {
        mint w = 1;
        for (int j = 0; j < m / 2; ++j) {
          auto t = w * A[k + j + m / 2];
          auto u = A[k + j];
          A[k + j] = u + t;
          A[k + j + m / 2] = u - t;
          w = w * wm;
        }
      }
    }
    return A;
  }

  int least_2pow(int x) {
    int ret = 1;
    while (ret < x)
      ret <<= 1;
    return ret;
  }

  vector<mint> multiply(const vector<mint>& _X, const vector<mint>& _Y) {
    vector<mint> X = _X, Y = _Y;
    const int n = least_2pow(X.size() + Y.size() - 1);
    X.resize(n);
    Y.resize(n);
    const int lgn = __builtin_ctz(n);
    vector<mint> fA(n);
    auto fX = trans(X, lgn, false);
    auto fY = trans(Y, lgn, false);
    for (int i = 0; i < n; ++i) {
      fA[i] = fX[i] * fY[i];
    }
    auto A = trans(fA, lgn, true);
    mint inv = mint(1) / n;
    for (int i = 0; i < n; ++i) {
      A[i] *= inv;
    }
    return A;
  }
};

int main() {
  NTT<998244353, 3> ntt;
  int n;
  cin >> n;
  vector<Fp<998244353>> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> a[i] >> b[i];
  auto c = ntt.multiply(a, b);
  for (int i = 1; i <= 2 * n; ++i)
    cout << c[i] << endl;

  return 0;
}