// https://sen-comp.hatenablog.com/entry/2021/02/06/180310
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
  friend constexpr istream& operator>>(istream& is, Fp<MOD>& x) noexcept {
    long long v{0};
    is >> v;
    x = v;
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

const long long MOD = 998244353;
using mint = Fp<MOD>;

typedef vector<mint> vectorM;  // NTT用のベクター型
const int DIVIDE_LIMIT = 23;  // 998244353の有名素数は23回分割統治できる
// ROOT[i] := 2^i乗根。998244353の有名素数の原始根は3で、
// 3^119 から2^23乗根を求め、
// そこから2^22乗根, 2^21...などをsetup() で計算する
mint ROOT[DIVIDE_LIMIT + 1];
// inv_ROOT[i] := 2^i乗根の逆数 setup()で計算
mint inv_ROOT[DIVIDE_LIMIT + 1];
mint PRIMITIVE_ROOT = 3;

void setup() {
  // 998244353 = 2^23 * 119 + 1
  ROOT[DIVIDE_LIMIT] = /* modpow(3, 119) */
      modpow(PRIMITIVE_ROOT, (MOD - 1) / modpow(mint(2), 23).val);
  inv_ROOT[DIVIDE_LIMIT] = mint(1) / ROOT[DIVIDE_LIMIT];
  for (int i = DIVIDE_LIMIT - 1; i >= 0; --i) {
    ROOT[i] = ROOT[i + 1] * ROOT[i + 1];
    inv_ROOT[i] = inv_ROOT[i + 1] * inv_ROOT[i + 1];
  }
}

vectorM ntt(const vectorM& f,
            const int inverse,
            const int log2_f,
            const int divide_cnt = DIVIDE_LIMIT) {
  vectorM ret;
  if (f.size() == 1 || divide_cnt == 0) {
    ret.resize(f.size());
    mint zeta = 1;
    for (int i = 0; i < ret.size(); ++i) {
      mint now = zeta;
      for (int j = 0; j < f.size(); ++j) {
        ret[i] += f[j] * now;
        now *= zeta;
      }
      zeta *= ((inverse == 1) ? ROOT[0] : inv_ROOT[0]);
    }
    return ret;
  }

  vectorM f1(f.size() / 2), f2(f.size() / 2);
  // f1とf2を作る
  for (int i = 0; i < f.size() / 2; ++i) {
    f1[i] = f[i * 2];
    f2[i] = f[i * 2 + 1];
  }

  vectorM f1_dft = ntt(f1, inverse, log2_f - 1, divide_cnt - 1);
  vectorM f2_dft = ntt(f2, inverse, log2_f - 1, divide_cnt - 1);
  ret.resize(f.size());
  mint now = 1;

  for (int i = 0; i < f.size(); ++i) {
    ret[i] = f1_dft[i % f1_dft.size()] + now * f2_dft[i % f2_dft.size()];
    now *= ((inverse == 1) ? ROOT[log2_f] : inv_ROOT[log2_f]);
  }
  return ret;
}

vectorM mulp(const vectorM& _f, const vectorM& _g) {
  vectorM f = _f, g = _g;

  // fとgの次数の和以上の最小の2冪-1とする
  int max_dim = 1, log2_max_dim = 0;
  while (f.size() + g.size() > max_dim)
    max_dim <<= 1, log2_max_dim += 1;
  f.resize(max_dim), g.resize(max_dim);

  // 多項式fとgのDFT結果を求める
  vectorM f_dft = ntt(f, 1, log2_max_dim);
  vectorM g_dft = ntt(g, 1, log2_max_dim);

  vectorM fg_dft(max_dim);
  for (int i = 0; i < max_dim; ++i) {
    fg_dft[i] = f_dft[i] * g_dft[i];
  }

  // fg_dftをDFT
  vectorM fg = ntt(fg_dft, -1, log2_max_dim);

  // 最後にmax_dimで割る
  for (int i = 0; i < fg.size(); ++i) {
    fg[i] /= max_dim;
  }
  return fg;
}

int main() {
  setup();
  int n, m;
  cin >> n >> m;
  vectorM a(n), b(m);
  repeat(i, n) cin >> a[i];
  repeat(i, m) cin >> b[i];
  auto c = mulp(a, b);
  repeat(i, n + m - 1) cout << c[i] << (i == n + m - 2 ? "\n" : " ");

  return 0;
}