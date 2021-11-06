// https://judge.yosupo.jp/submission/56073
#pragma GCC optimize("O3")
#pragma GCC target("avx2")

#include <bits/stdc++.h>

using namespace std;

using int64 = long long;
// const int mod = 1e9 + 7;
const int mod = 998244353;

const int64 infll = (1LL << 62) - 1;
const int inf = (1 << 30) - 1;

struct IoSetup {
  IoSetup() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cerr << fixed << setprecision(10);
  }
} iosetup;

template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
  os << p.first << " " << p.second;
  return os;
}

template <typename T1, typename T2>
istream& operator>>(istream& is, pair<T1, T2>& p) {
  is >> p.first >> p.second;
  return is;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << (i + 1 != v.size() ? " " : "");
  }
  return os;
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
  for (T& in : v)
    is >> in;
  return is;
}

template <typename T1, typename T2>
inline bool chmax(T1& a, T2 b) {
  return a < b && (a = b, true);
}

template <typename T1, typename T2>
inline bool chmin(T1& a, T2 b) {
  return a > b && (a = b, true);
}

template <typename T = int64>
vector<T> make_v(size_t a) {
  return vector<T>(a);
}

template <typename T, typename... Ts>
auto make_v(size_t a, Ts... ts) {
  return vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}

template <typename T, typename V>
typename enable_if<is_class<T>::value == 0>::type fill_v(T& t, const V& v) {
  t = v;
}

template <typename T, typename V>
typename enable_if<is_class<T>::value != 0>::type fill_v(T& t, const V& v) {
  for (auto& e : t)
    fill_v(e, v);
}

template <typename F>
struct FixPoint : F {
  FixPoint(F&& f) : F(forward<F>(f)) {}

  template <typename... Args>
  decltype(auto) operator()(Args&&... args) const {
    return F::operator()(*this, forward<Args>(args)...);
  }
};

template <typename F>
inline decltype(auto) MFP(F&& f) {
  return FixPoint<F>{forward<F>(f)};
}

/**
 * @brief Montgomery Mod Int
 */
template <uint32_t mod, bool fast = false>
struct MontgomeryModInt {
  using mint = MontgomeryModInt;
  using i32 = int32_t;
  using i64 = int64_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; i++)
      ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;

  static_assert(r * mod == 1, "invalid, r * mod != 1");
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");

  u32 x;

  MontgomeryModInt() : x{} {}

  MontgomeryModInt(const i64& a)
      : x(reduce(u64(fast ? a : (a % mod + mod)) * n2)) {}

  static constexpr u32 reduce(const u64& b) {
    return u32(b >> 32) + mod - u32((u64(u32(b) * r) * mod) >> 32);
  }

  mint& operator+=(const mint& p) {
    if (i32(x += p.x - 2 * mod) < 0)
      x += 2 * mod;
    return *this;
  }

  mint& operator-=(const mint& p) {
    if (i32(x -= p.x) < 0)
      x += 2 * mod;
    return *this;
  }

  mint& operator*=(const mint& p) {
    x = reduce(u64(x) * p.x);
    return *this;
  }

  mint& operator/=(const mint& p) {
    *this *= p.inverse();
    return *this;
  }

  mint operator-() const { return mint() - *this; }

  mint operator+(const mint& p) const { return mint(*this) += p; }

  mint operator-(const mint& p) const { return mint(*this) -= p; }

  mint operator*(const mint& p) const { return mint(*this) *= p; }

  mint operator/(const mint& p) const { return mint(*this) /= p; }

  bool operator==(const mint& p) const {
    return (x >= mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x);
  }

  bool operator!=(const mint& p) const {
    return (x >= mod ? x - mod : x) != (p.x >= mod ? p.x - mod : p.x);
  }

  u32 get() const {
    u32 ret = reduce(x);
    return ret >= mod ? ret - mod : ret;
  }

  mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1)
        ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  mint inverse() const { return pow(mod - 2); }

  friend ostream& operator<<(ostream& os, const mint& p) {
    return os << p.get();
  }

  friend istream& operator>>(istream& is, mint& a) {
    i64 t;
    is >> t;
    a = mint(t);
    return is;
  }

  static constexpr u32 get_mod() { return mod; }
};

#include <immintrin.h>

struct alignas(32) VectorizeModInt {
  using Mints = VectorizeModInt;
  using i32 = int32_t;
  using i64 = int64_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static __m256i m0, m1, m2, r1;

  template <typename Mint>
  static void set_mod() {
    r1 = _mm256_set1_epi32(Mint::r);
    m0 = _mm256_setzero_si256();
    m1 = _mm256_set1_epi32(Mint::get_mod());
    m2 = _mm256_set1_epi32(Mint::get_mod() * 2);
  }

  __m256i x;

  VectorizeModInt() : x{} {}

  inline VectorizeModInt(const i32& v) : x(_mm256_set1_epi32(v)) {}

  inline VectorizeModInt(const i32& v0,
                         const i32& v1,
                         const i32& v2,
                         const i32& v3,
                         const i32& v4,
                         const i32& v5,
                         const i32& v6,
                         const i32& v7)
      : x(_mm256_setr_epi32(v0, v1, v2, v3, v4, v5, v6, v7)) {}

  inline VectorizeModInt(const void* vs)
      : x(_mm256_loadu_si256((__m256i*)vs)) {}

  inline void store(const void* vs) { _mm256_storeu_si256((__m256i*)vs, x); }

  static inline __m256i _mm256_mulhi_epi32(const __m256i& a, const __m256i& b) {
    auto a13 = _mm256_shuffle_epi32(a, 0xf5);
    auto b13 = _mm256_shuffle_epi32(b, 0xf5);
    auto prod02 = _mm256_mul_epu32(a, b);
    auto prod13 = _mm256_mul_epu32(a13, b13);
    auto prod = _mm256_unpackhi_epi64(_mm256_unpacklo_epi32(prod02, prod13),
                                      _mm256_unpackhi_epi32(prod02, prod13));
    return prod;
  }

  static inline __m256i reduce(const __m256i& lo, const __m256i& hi) {
    // u32(b >> 32) + mod - u32((u64(u32(b) * r) * mod) >> 32)
    auto c = _mm256_mulhi_epi32(_mm256_mullo_epi32(lo, r1), m1);
    return _mm256_add_epi32(_mm256_sub_epi32(hi, c), m1);
  }

  Mints inline& operator+=(const Mints& p) {
    // if(int(x += p.x - 2 * mod) < 0) x += 2 * mod;
    const auto c = _mm256_sub_epi32(_mm256_add_epi32(x, p.x), m2);
    x = _mm256_add_epi32(c, _mm256_and_si256(_mm256_cmpgt_epi32(m0, c), m2));
    return *this;
  }

  Mints inline& operator-=(const Mints& p) {
    // if(int(x -= p.x) < 0) x += 2 * mod;
    const auto c = _mm256_sub_epi32(x, p.x);
    x = _mm256_add_epi32(c, _mm256_and_si256(_mm256_cmpgt_epi32(m0, c), m2));
    return *this;
  }

  Mints inline& operator*=(const Mints& p) {
    x = reduce(_mm256_mullo_epi32(x, p.x), _mm256_mulhi_epi32(x, p.x));
    return *this;
  }

  Mints inline operator+(const Mints& p) const { return Mints(*this) += p; }

  Mints inline operator-(const Mints& p) const { return Mints(*this) -= p; }

  Mints inline operator*(const Mints& p) const { return Mints(*this) *= p; }
};

__attribute__((aligned(32))) __m256i VectorizeModInt::m0;
__attribute__((aligned(32))) __m256i VectorizeModInt::m1;
__attribute__((aligned(32))) __m256i VectorizeModInt::m2;
__attribute__((aligned(32))) __m256i VectorizeModInt::r1;

using modint = MontgomeryModInt<mod, true>;

template <typename Mint>
struct NumberTheoreticTransformFriendlyModInt {
  static vector<Mint> roots, iroots, rate2, rate3, irate2, irate3;
  static int max_base;
  static Mint root;

  NumberTheoreticTransformFriendlyModInt() = default;

  static void init() {
    if (roots.empty()) {
      const unsigned mod = Mint::get_mod();
      assert(mod >= 3 && mod % 2 == 1);
      auto tmp = mod - 1;
      max_base = 0;
      while (tmp % 2 == 0)
        tmp >>= 1, max_base++;
      root = 2;
      while (root.pow((mod - 1) >> 1) == 1) {
        root += 1;
      }
      assert(root.pow(mod - 1) == 1);

      roots.resize(max_base + 1);
      iroots.resize(max_base + 1);
      rate2.resize(max_base + 1);
      irate2.resize(max_base + 1);
      rate3.resize(max_base + 1);
      irate3.resize(max_base + 1);

      roots[max_base] = root.pow((mod - 1) >> max_base);
      iroots[max_base] = Mint(1) / roots[max_base];
      for (int i = max_base - 1; i >= 0; i--) {
        roots[i] = roots[i + 1] * roots[i + 1];
        iroots[i] = iroots[i + 1] * iroots[i + 1];
      }
      {
        Mint prod = 1, iprod = 1;
        for (int i = 0; i <= max_base - 2; i++) {
          rate2[i] = roots[i + 2] * prod;
          irate2[i] = iroots[i + 2] * iprod;
          prod *= iroots[i + 2];
          iprod *= roots[i + 2];
        }
      }
      {
        Mint prod = 1, iprod = 1;
        for (int i = 0; i <= max_base - 3; i++) {
          rate3[i] = roots[i + 3] * prod;
          irate3[i] = iroots[i + 3] * iprod;
          prod *= iroots[i + 3];
          iprod *= roots[i + 3];
        }
      }
    }
  }

  static void ntt(vector<Mint>& a) {
    init();
    const int n = (int)a.size();
    assert((n & (n - 1)) == 0);
    int h = __builtin_ctz(n);
    assert(h <= max_base);
    int len = 0;
    if (h & 1) {
      int p = 1 << (h - 1);
      if (p < 8) {
        for (int i = 0; i < p; i++) {
          auto r = a[i + p];
          a[i + p] = a[i] - r;
          a[i] += r;
        }
      } else {
        for (int i = 0; i < p; i += 8) {
          VectorizeModInt ls(&a[i]);
          VectorizeModInt rs(&a[i + p]);
          (ls - rs).store(&a[i + p]);
          (ls + rs).store(&a[i]);
        }
      }
      len++;
    }
    for (; len + 1 < h; len += 2) {
      int p = 1 << (h - len - 2);
      Mint imag = roots[2];
      {  // s = 0
        for (int i = 0; i < p; i++) {
          auto a0 = a[i];
          auto a1 = a[i + p];
          auto a2 = a[i + 2 * p];
          auto a3 = a[i + 3 * p];
          auto a1na3imag = (a1 - a3) * imag;
          auto a0a2 = a0 + a2;
          auto a1a3 = a1 + a3;
          auto a0na2 = a0 - a2;
          a[i] = a0a2 + a1a3;
          a[i + 1 * p] = a0a2 - a1a3;
          a[i + 2 * p] = a0na2 + a1na3imag;
          a[i + 3 * p] = a0na2 - a1na3imag;
        }
      }
      Mint rot = rate3[__builtin_ctz(~0)];
      if (p <= 4) {
        for (int s = 1; s < (1 << len); s++) {
          int offset = s << (h - len);
          Mint rot2 = rot * rot;
          Mint rot3 = rot2 * rot;
          for (int i = 0; i < p; i++) {
            auto a0 = a[i + offset];
            auto a1 = a[i + offset + p] * rot;
            auto a2 = a[i + offset + 2 * p] * rot2;
            auto a3 = a[i + offset + 3 * p] * rot3;
            auto a1na3imag = (a1 - a3) * imag;
            auto a0a2 = a0 + a2;
            auto a1a3 = a1 + a3;
            auto a0na2 = a0 - a2;
            a[i + offset] = a0a2 + a1a3;
            a[i + offset + 1 * p] = a0a2 - a1a3;
            a[i + offset + 2 * p] = a0na2 + a1na3imag;
            a[i + offset + 3 * p] = a0na2 - a1na3imag;
          }
          rot *= rate3[__builtin_ctz(~s)];
        }
      } else {
        VectorizeModInt imags(imag.x);
        for (int s = 1; s < (1 << len); s++) {
          int offset = s << (h - len);
          Mint rot2 = rot * rot;
          Mint rot3 = rot2 * rot;
          VectorizeModInt rot1s(rot.x);
          VectorizeModInt rot2s(rot2.x);
          VectorizeModInt rot3s(rot3.x);
          for (int i = 0; i < p; i += 8) {
            VectorizeModInt a0(&a[i + offset]);
            VectorizeModInt a1(&a[i + offset + p]);
            VectorizeModInt a2(&a[i + offset + 2 * p]);
            VectorizeModInt a3(&a[i + offset + 3 * p]);
            a1 *= rot1s;
            a2 *= rot2s;
            a3 *= rot3s;
            auto a1na3imag = (a1 - a3) * imags;
            auto a0a2 = a0 + a2;
            auto a1a3 = a1 + a3;
            auto a0na2 = a0 - a2;
            (a0a2 + a1a3).store(&a[i + offset]);
            (a0a2 - a1a3).store(&a[i + offset + p]);
            (a0na2 + a1na3imag).store(&a[i + offset + 2 * p]);
            (a0na2 - a1na3imag).store(&a[i + offset + 3 * p]);
          }
          rot *= rate3[__builtin_ctz(~s)];
        }
      }
    }
  }

  static void intt(vector<Mint>& a, bool f = true) {
    init();
    const int n = (int)a.size();
    assert((n & (n - 1)) == 0);
    int h = __builtin_ctz(n);
    assert(h <= max_base);
    int len = h;
    for (; len > 1; len -= 2) {
      int p = 1 << (h - len);
      Mint iimag = iroots[2];
      {  // s = 0
        for (int i = 0; i < p; i++) {
          auto a0 = a[i];
          auto a1 = a[i + 1 * p];
          auto a2 = a[i + 2 * p];
          auto a3 = a[i + 3 * p];
          auto a2na3iimag = (a2 - a3) * iimag;
          auto a0na1 = a0 - a1;
          auto a0a1 = a0 + a1;
          auto a2a3 = a2 + a3;
          a[i] = a0a1 + a2a3;
          a[i + 1 * p] = (a0na1 + a2na3iimag);
          a[i + 2 * p] = (a0a1 - a2a3);
          a[i + 3 * p] = (a0na1 - a2na3iimag);
        }
      }
      Mint irot = irate3[__builtin_ctz(~0)];

      if (p <= 4) {
        for (int s = 1; s < (1 << (len - 2)); s++) {
          int offset = s << (h - len + 2);
          Mint irot2 = irot * irot;
          Mint irot3 = irot2 * irot;
          for (int i = 0; i < p; i++) {
            auto a0 = a[i + offset];
            auto a1 = a[i + offset + 1 * p];
            auto a2 = a[i + offset + 2 * p];
            auto a3 = a[i + offset + 3 * p];
            auto a2na3iimag = (a2 - a3) * iimag;
            auto a0na1 = a0 - a1;
            auto a0a1 = a0 + a1;
            auto a2a3 = a2 + a3;
            a[i + offset] = a0a1 + a2a3;
            a[i + offset + 1 * p] = (a0na1 + a2na3iimag) * irot;
            a[i + offset + 2 * p] = (a0a1 - a2a3) * irot2;
            a[i + offset + 3 * p] = (a0na1 - a2na3iimag) * irot3;
          }
          irot *= irate3[__builtin_ctz(~s)];
        }
      } else {
        VectorizeModInt iimags(iimag.x);
        for (int s = 1; s < (1 << (len - 2)); s++) {
          int offset = s << (h - len + 2);
          Mint irot2 = irot * irot;
          Mint irot3 = irot2 * irot;
          VectorizeModInt irot1s(irot.x);
          VectorizeModInt irot2s(irot2.x);
          VectorizeModInt irot3s(irot3.x);
          for (int i = 0; i < p; i += 8) {
            VectorizeModInt a0(&a[i + offset]);
            VectorizeModInt a1(&a[i + offset + p]);
            VectorizeModInt a2(&a[i + offset + 2 * p]);
            VectorizeModInt a3(&a[i + offset + 3 * p]);
            auto a2na3iimag = (a2 - a3) * iimags;
            auto a0na1 = a0 - a1;
            auto a0a1 = a0 + a1;
            auto a2a3 = a2 + a3;
            (a0a1 + a2a3).store(&a[i + offset]);
            ((a0na1 + a2na3iimag) * irot1s).store(&a[i + offset + p]);
            ((a0a1 - a2a3) * irot2s).store(&a[i + offset + 2 * p]);
            ((a0na1 - a2na3iimag) * irot3s).store(&a[i + offset + 3 * p]);
          }
          irot *= irate3[__builtin_ctz(~s)];
        }
      }
    }
    if (len >= 1) {
      int p = 1 << (h - 1);
      if (p < 8) {
        for (int i = 0; i < p; i++) {
          auto ajp = a[i] - a[i + p];
          a[i] += a[i + p];
          a[i + p] = ajp;
        }
      } else {
        for (int i = 0; i < p; i += 8) {
          VectorizeModInt ls(&a[i]);
          VectorizeModInt rs(&a[i + p]);
          (ls + rs).store(&a[i]);
          (ls - rs).store(&a[i + p]);
        }
      }
    }
    if (f) {
      Mint inv_sz = Mint(1) / n;
      for (int i = 0; i < n; i++)
        a[i] *= inv_sz;
    }
  }

  static vector<Mint> multiply(vector<Mint> a, vector<Mint> b) {
    int need = a.size() + b.size() - 1;
    int nbase = 1;
    while ((1 << nbase) < need)
      nbase++;
    int sz = 1 << nbase;
    a.resize(sz, 0);
    b.resize(sz, 0);
    ntt(a);
    ntt(b);
    Mint inv_sz = Mint(1) / sz;
    if (sz % 8 == 0) {
      VectorizeModInt invs(inv_sz.x);
      for (int i = 0; i < sz; i += 8) {
        VectorizeModInt as(&a[i]);
        VectorizeModInt bs(&b[i]);
        (as * bs * invs).store(&a[i]);
      }
    } else {
      for (int i = 0; i < sz; i++) {
        a[i] *= b[i] * inv_sz;
      }
    }
    intt(a, false);
    a.resize(need);
    return a;
  }
};

template <typename Mint>
vector<Mint> NumberTheoreticTransformFriendlyModInt<Mint>::roots =
    vector<Mint>();
template <typename Mint>
vector<Mint> NumberTheoreticTransformFriendlyModInt<Mint>::iroots =
    vector<Mint>();
template <typename Mint>
vector<Mint> NumberTheoreticTransformFriendlyModInt<Mint>::rate2 =
    vector<Mint>();
template <typename Mint>
vector<Mint> NumberTheoreticTransformFriendlyModInt<Mint>::irate2 =
    vector<Mint>();
template <typename Mint>
vector<Mint> NumberTheoreticTransformFriendlyModInt<Mint>::rate3 =
    vector<Mint>();
template <typename Mint>
vector<Mint> NumberTheoreticTransformFriendlyModInt<Mint>::irate3 =
    vector<Mint>();
template <typename Mint>
int NumberTheoreticTransformFriendlyModInt<Mint>::max_base = 0;
template <typename Mint>
Mint NumberTheoreticTransformFriendlyModInt<Mint>::root = Mint();

/**
 * @brief Formal Power Series Friendly NTT(NTTmod用形式的冪級数)
 * @docs docs/formal-power-series-friendly-ntt.md
 */
template <typename T>
struct FormalPowerSeriesFriendlyNTT : vector<T> {
  using vector<T>::vector;
  using P = FormalPowerSeriesFriendlyNTT;
  using NTT = NumberTheoreticTransformFriendlyModInt<T>;

  P pre(int deg) const {
    return P(begin(*this), begin(*this) + min((int)this->size(), deg));
  }

  P rev(int deg = -1) const {
    P ret(*this);

    if (deg != -1)
      ret.resize(deg, T(0));

    reverse(begin(ret), end(ret));
    return ret;
  }

  void shrink() {
    while (this->size() && this->back() == T(0))
      this->pop_back();
  }

  P operator+(const P& r) const { return P(*this) += r; }

  P operator+(const T& v) const { return P(*this) += v; }

  P operator-(const P& r) const { return P(*this) -= r; }

  P operator-(const T& v) const { return P(*this) -= v; }

  P operator*(const P& r) const { return P(*this) *= r; }

  P operator*(const T& v) const { return P(*this) *= v; }

  P operator/(const P& r) const { return P(*this) /= r; }

  P operator%(const P& r) const { return P(*this) %= r; }

  P& operator+=(const P& r) {
    if (r.size() > this->size())
      this->resize(r.size());

    for (int i = 0; i < (int)r.size(); i++)
      (*this)[i] += r[i];

    return *this;
  }

  P& operator-=(const P& r) {
    if (r.size() > this->size())
      this->resize(r.size());

    for (int i = 0; i < (int)r.size(); i++)
      (*this)[i] -= r[i];

    return *this;
  }

  // https://judge.yosupo.jp/problem/convolution_mod
  P& operator*=(const P& r) {
    if (this->empty() || r.empty()) {
      this->clear();
      return *this;
    }

    auto ret = NTT::multiply(*this, r);
    return *this = {begin(ret), end(ret)};
  }

  P& operator/=(const P& r) {
    if (this->size() < r.size()) {
      this->clear();
      return *this;
    }

    int n = this->size() - r.size() + 1;
    return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);
  }

  P& operator%=(const P& r) {
    *this -= *this / r * r;
    shrink();
    return *this;
  }

  // https://judge.yosupo.jp/problem/division_of_polynomials
  pair<P, P> div_mod(const P& r) {
    P q = *this / r;
    P x = *this - q * r;
    x.shrink();
    return make_pair(q, x);
  }

  P operator-() const {
    P ret(this->size());

    for (int i = 0; i < (int)this->size(); i++)
      ret[i] = -(*this)[i];

    return ret;
  }

  P& operator+=(const T& r) {
    if (this->empty())
      this->resize(1);

    (*this)[0] += r;
    return *this;
  }

  P& operator-=(const T& r) {
    if (this->empty())
      this->resize(1);

    (*this)[0] -= r;
    return *this;
  }

  P& operator*=(const T& v) {
    for (int i = 0; i < (int)this->size(); i++)
      (*this)[i] *= v;

    return *this;
  }

  P dot(P r) const {
    P ret(min(this->size(), r.size()));

    for (int i = 0; i < (int)ret.size(); i++)
      ret[i] = (*this)[i] * r[i];

    return ret;
  }

  P operator>>(int sz) const {
    if ((int)this->size() <= sz)
      return {};

    P ret(*this);

    ret.erase(ret.begin(), ret.begin() + sz);

    return ret;
  }

  P operator<<(int sz) const {
    P ret(*this);
    ret.insert(ret.begin(), sz, T(0));
    return ret;
  }

  T operator()(T x) const {
    T r = 0, w = 1;

    for (auto& v : *this) {
      r += w * v;
      w *= x;
    }

    return r;
  }

  P diff() const {
    const int n = (int)this->size();
    P ret(max(0, n - 1));

    for (int i = 1; i < n; i++)
      ret[i - 1] = (*this)[i] * T(i);

    return ret;
  }

  P integral() const {
    const int n = (int)this->size();
    P ret(n + 1);
    ret[0] = T(0);

    for (int i = 0; i < n; i++)
      ret[i + 1] = (*this)[i] / T(i + 1);

    return ret;
  }

  // https://judge.yosupo.jp/problem/inv_of_formal_power_series
  // F(0) must not be 0
  P inv(int deg = -1) const {
    assert(((*this)[0]) != T(0));
    const int n = (int)this->size();

    if (deg == -1)
      deg = n;

    P res(deg);
    res[0] = {T(1) / (*this)[0]};

    for (int d = 1; d < deg; d <<= 1) {
      P f(2 * d), g(2 * d);

      for (int j = 0; j < min(n, 2 * d); j++)
        f[j] = (*this)[j];

      for (int j = 0; j < d; j++)
        g[j] = res[j];

      NTT::ntt(f);
      NTT::ntt(g);
      f = f.dot(g);
      NTT::intt(f);

      for (int j = 0; j < d; j++)
        f[j] = 0;

      NTT::ntt(f);

      for (int j = 0; j < 2 * d; j++)
        f[j] *= g[j];

      NTT::intt(f);

      for (int j = d; j < min(2 * d, deg); j++)
        res[j] = -f[j];
    }

    return res;
  }

  // https://judge.yosupo.jp/problem/log_of_formal_power_series
  // F(0) must be 1
  P log(int deg = -1) const {
    assert((*this)[0] == T(1));
    const int n = (int)this->size();

    if (deg == -1)
      deg = n;

    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
  }

  // https://judge.yosupo.jp/problem/sqrt_of_formal_power_series
  P sqrt(
      int deg = -1,
      const function<T(T)>& get_sqrt = [](T) { return T(1); }) const {
    const int n = (int)this->size();

    if (deg == -1)
      deg = n;

    if ((*this)[0] == T(0)) {
      for (int i = 1; i < n; i++) {
        if ((*this)[i] != T(0)) {
          if (i & 1)
            return {};

          if (deg - i / 2 <= 0)
            break;

          auto ret = (*this >> i).sqrt(deg - i / 2, get_sqrt);

          if (ret.empty())
            return {};

          ret = ret << (i / 2);

          if ((int)ret.size() < deg)
            ret.resize(deg, T(0));

          return ret;
        }
      }

      return P(deg, 0);
    }

    auto sqr = T(get_sqrt((*this)[0]));

    if (sqr * sqr != (*this)[0])
      return {};

    P ret{sqr};

    T inv2 = T(1) / T(2);

    for (int i = 1; i < deg; i <<= 1) {
      ret = (ret + pre(i << 1) * ret.inv(i << 1)) * inv2;
    }

    return ret.pre(deg);
  }

  P sqrt(const function<T(T)>& get_sqrt, int deg = -1) const {
    return sqrt(deg, get_sqrt);
  }

  // https://judge.yosupo.jp/problem/exp_of_formal_power_series
  // F(0) must be 0
  P exp(int deg = -1) const {
    if (deg == -1)
      deg = this->size();

    assert((*this)[0] == T(0));

    P inv;
    inv.reserve(deg + 1);
    inv.push_back(T(0));
    inv.push_back(T(1));

    auto inplace_integral = [&](P& F) -> void {
      const int n = (int)F.size();
      auto mod = T::get_mod();

      while ((int)inv.size() <= n) {
        int i = inv.size();
        inv.push_back((-inv[mod % i]) * (mod / i));
      }

      F.insert(begin(F), T(0));

      for (int i = 1; i <= n; i++)
        F[i] *= inv[i];
    };

    auto inplace_diff = [](P& F) -> void {
      if (F.empty())
        return;

      F.erase(begin(F));
      T coeff = 1, one = 1;

      for (int i = 0; i < (int)F.size(); i++) {
        F[i] *= coeff;
        coeff += one;
      }
    };

    P b{1, 1 < (int)this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};

    for (int m = 2; m < deg; m *= 2) {
      auto y = b;
      y.resize(2 * m);
      NTT::ntt(y);
      z1 = z2;
      P z(m);

      for (int i = 0; i < m; ++i)
        z[i] = y[i] * z1[i];

      NTT::intt(z);
      fill(begin(z), begin(z) + m / 2, T(0));
      NTT::ntt(z);

      for (int i = 0; i < m; ++i)
        z[i] *= -z1[i];

      NTT::intt(z);
      c.insert(end(c), begin(z) + m / 2, end(z));
      z2 = c;
      z2.resize(2 * m);
      NTT::ntt(z2);
      P x(begin(*this), begin(*this) + min<int>(this->size(), m));
      inplace_diff(x);
      x.push_back(T(0));
      NTT::ntt(x);

      for (int i = 0; i < m; ++i)
        x[i] *= y[i];

      NTT::intt(x);
      x -= b.diff();
      x.resize(2 * m);

      for (int i = 0; i < m - 1; ++i)
        x[m + i] = x[i], x[i] = T(0);

      NTT::ntt(x);

      for (int i = 0; i < 2 * m; ++i)
        x[i] *= z2[i];

      NTT::intt(x);
      x.pop_back();
      inplace_integral(x);

      for (int i = m; i < min<int>(this->size(), 2 * m); ++i)
        x[i] += (*this)[i];

      fill(begin(x), begin(x) + m, T(0));
      NTT::ntt(x);

      for (int i = 0; i < 2 * m; ++i)
        x[i] *= y[i];

      NTT::intt(x);
      b.insert(end(b), begin(x) + m, end(x));
    }

    return P{begin(b), begin(b) + deg};
  }

  // https://judge.yosupo.jp/problem/pow_of_formal_power_series
  P pow(int64_t k, int deg = -1) const {
    const int n = (int)this->size();

    if (deg == -1)
      deg = n;

    for (int i = 0; i < n; i++) {
      if ((*this)[i] != T(0)) {
        T rev = T(1) / (*this)[i];
        P ret = (((*this * rev) >> i).log() * k).exp() * ((*this)[i].pow(k));

        if (i * k > deg)
          return P(deg, T(0));

        ret = (ret << (i * k)).pre(deg);

        if ((int)ret.size() < deg)
          ret.resize(deg, T(0));

        return ret;
      }
    }

    return *this;
  }

  P mod_pow(int64_t k, P g) const {
    P modinv = g.rev().inv();
    auto get_div = [&](P base) {
      if (base.size() < g.size()) {
        base.clear();
        return base;
      }

      int n = base.size() - g.size() + 1;
      return (base.rev().pre(n) * modinv.pre(n)).pre(n).rev(n);
    };
    P x(*this), ret{1};

    while (k > 0) {
      if (k & 1) {
        ret *= x;
        ret -= get_div(ret) * g;
        ret.shrink();
      }

      x *= x;
      x -= get_div(x) * g;
      x.shrink();
      k >>= 1;
    }

    return ret;
  }

  // https://judge.yosupo.jp/problem/polynomial_taylor_shift
  P taylor_shift(T c) const {
    int n = (int)this->size();
    vector<T> fact(n), rfact(n);
    fact[0] = rfact[0] = T(1);

    for (int i = 1; i < n; i++)
      fact[i] = fact[i - 1] * T(i);

    rfact[n - 1] = T(1) / fact[n - 1];

    for (int i = n - 1; i > 1; i--)
      rfact[i - 1] = rfact[i] * T(i);

    P p(*this);

    for (int i = 0; i < n; i++)
      p[i] *= fact[i];

    p = p.rev();
    P bs(n, T(1));

    for (int i = 1; i < n; i++)
      bs[i] = bs[i - 1] * c * rfact[i] * fact[i - 1];

    p = (p * bs).pre(n);
    p = p.rev();

    for (int i = 0; i < n; i++)
      p[i] *= rfact[i];

    return p;
  }
};

template <typename Mint>
using FPS = FormalPowerSeriesFriendlyNTT<Mint>;

template <typename T>
T mod_pow(T x, T n, const T& p) {
  T ret = 1;

  while (n > 0) {
    if (n & 1)
      (ret *= x) %= p;

    (x *= x) %= p;
    n >>= 1;
  }

  return ret;
}

/**
 * @brief Mod Sqrt
 */
template <typename T>
T mod_sqrt(const T& a, const T& p) {
  if (a == 0)
    return 0;

  if (p == 2)
    return a;

  if (mod_pow(a, (p - 1) >> 1, p) != 1)
    return -1;

  T b = 1;

  while (mod_pow(b, (p - 1) >> 1, p) == 1)
    ++b;

  T e = 0, m = p - 1;

  while (m % 2 == 0)
    m >>= 1, ++e;

  T x = mod_pow(a, (m - 1) >> 1, p);
  T y = a * (x * x % p) % p;
  (x *= a) %= p;
  T z = mod_pow(b, m, p);

  while (y != 1) {
    T j = 0, t = y;

    while (t != 1) {
      j += 1;
      (t *= t) %= p;
    }

    z = mod_pow(z, T(1) << (e - j - 1), p);
    (x *= z) %= p;
    (z *= z) %= p;
    (y *= z) %= p;
    e = j;
  }

  return min(x, p - x);
}

/**
 * @brief Scanner(高速入力)
 */
struct Scanner {
 public:
  explicit Scanner(FILE* fp) : fp(fp) {}

  template <typename T, typename... E>
  void read(T& t, E&... e) {
    read_single(t);
    read(e...);
  }

 private:
  static constexpr size_t line_size = 1 << 16;
  static constexpr size_t int_digits = 20;
  char line[line_size + 1] = {};
  FILE* fp = nullptr;
  char* st = line;
  char* ed = line;

  void read() {}

  static inline bool is_space(char c) { return c <= ' '; }

  void reread() {
    ptrdiff_t len = ed - st;
    memmove(line, st, len);
    char* tmp = line + len;
    ed = tmp + fread(tmp, 1, line_size - len, fp);
    *ed = 0;
    st = line;
  }

  void skip_space() {
    while (true) {
      if (st == ed)
        reread();
      while (*st && is_space(*st))
        ++st;
      if (st != ed)
        return;
    }
  }

  template <typename T, enable_if_t<is_integral<T>::value, int> = 0>
  void read_single(T& s) {
    skip_space();
    if (st + int_digits >= ed)
      reread();
    bool neg = false;
    if (is_signed<T>::value && *st == '-') {
      neg = true;
      ++st;
    }
    typename make_unsigned<T>::type y = *st++ - '0';
    while (*st >= '0') {
      y = 10 * y + *st++ - '0';
    }
    s = (neg ? -y : y);
  }

  template <typename T, enable_if_t<is_same<T, string>::value, int> = 0>
  void read_single(T& s) {
    s = "";
    skip_space();
    while (true) {
      char* base = st;
      while (*st && !is_space(*st))
        ++st;
      s += string(base, st);
      if (st != ed)
        return;
      reread();
    }
  }

  template <typename T>
  void read_single(vector<T>& s) {
    for (auto& d : s)
      read(d);
  }
};

/**
 * @brief Printer(高速出力)
 */
struct Printer {
 public:
  explicit Printer(FILE* fp) : fp(fp) {}

  ~Printer() { flush(); }

  template <bool f = false, typename T, typename... E>
  void write(const T& t, const E&... e) {
    if (f)
      write_single(' ');
    write_single(t);
    write<true>(e...);
  }

  template <typename... T>
  void writeln(const T&... t) {
    write(t...);
    write_single('\n');
  }

  void flush() {
    fwrite(line, 1, st - line, fp);
    st = line;
  }

 private:
  FILE* fp = nullptr;
  static constexpr size_t line_size = 1 << 16;
  static constexpr size_t int_digits = 20;
  char line[line_size + 1] = {};
  char small[32] = {};
  char* st = line;

  template <bool f = false>
  void write() {}

  void write_single(const char& t) {
    if (st + 1 >= line + line_size)
      flush();
    *st++ = t;
  }

  template <typename T, enable_if_t<is_integral<T>::value, int> = 0>
  void write_single(T s) {
    if (st + int_digits >= line + line_size)
      flush();
    if (s == 0) {
      write_single('0');
      return;
    }
    if (s < 0) {
      write_single('-');
      s = -s;
    }
    char* mp = small + sizeof(small);
    typename make_unsigned<T>::type y = s;
    size_t len = 0;
    while (y > 0) {
      *--mp = y % 10 + '0';
      y /= 10;
      ++len;
    }
    memmove(st, mp, len);
    st += len;
  }

  void write_single(const string& s) {
    for (auto& c : s)
      write_single(c);
  }

  void write_single(const char* s) {
    while (*s != 0)
      write_single(*s++);
  }

  template <typename T>
  void write_single(const vector<T>& s) {
    for (size_t i = 0; i < s.size(); i++) {
      if (i)
        write_single(' ');
      write_single(s[i]);
    }
  }
};

int main() {
  VectorizeModInt::set_mod<modint>();
  int N;
  cin >> N;
  FPS<modint> f(N);
  for (auto& p : f) {
    int x;
    cin >> x;
    p = x;
  }
  f = f.inv();
  for (int i = 0; i < N; i++) {
    if (i)
      cout << ' ';
    cout << f[i].get();
  }
  cout << endl;
}
