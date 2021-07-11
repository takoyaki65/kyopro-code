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

// https://www.slideshare.net/hcpc_hokudai/binary-indexed-tree
template <typename T>
struct BIT {
 private:
  vector<T> array;
  const int n;

  T sum_Oneindexed(int i) {
    T s = 0;
    while (i > 0) {
      s += array[i];
      i -= i & -i;  // LSB減算
    }
    return s;
  }

  void add_OneIndexed(int i, T x) {
    while (i <= n) {
      array[i] += x;
      i += i & -i;  // LSB加算
    }
  }

 public:
  BIT(int _n) : array(_n + 1, 0), n(_n) {}

  // [0, i]までの累積和
  T sum(int i) {
    assert(i >= 0);
    return sum_Oneindexed(++i);
  }

  // [i, j]の要素の総和
  T sum(int i, int j) {
    assert(i >= 0 && i <= j);
    return sum_Oneindexed(++j) - sum_Oneindexed((++i) - 1);
  }

  // i番目に要素xを追加
  void add(int i, T x) { add_OneIndexed(++i, x); }
};

int N;
long long K;
int A[200005];
// cl[r] := 区間[l,r]の転倒数がK以下となる最小のl
int cl[200005];

// dp[r+1] := r番目の要素まで考えたときの、分割方法の総数
// 区間[cl[r], r], [cl[r]+1, r], ... , [r,r]が1つのピースになりえるので
// dp[r+1] = dp[cl[r]] + dp[cl[r] + 1] + ... + dp[r-1] + dp[r]
// dp[0] = 1
mint dp[200005], dp2[200005];

// dp2[i] = dp[0] + dp[1] + ... + dp[i] = dp[i] + dp2[i-1]
// dp2[0] = 1

// dp[r+1] = dp2[r] - dp2[cl[r]-1]
// dp2[r+1] = dp2[r] + dp[r+1]

int main() {
  cin >> N >> K;
  repeat(i, N) cin >> A[i];

  // 座標圧縮
  {
    vector<int> vals(A, A + N);
    sort(vals.begin(), vals.end());
    auto itr = unique(vals.begin(), vals.end());
    vals.erase(itr, vals.end());
    repeat(i, N) {
      int id = lower_bound(vals.begin(), vals.end(), A[i]) - vals.begin();
      A[i] = id + 5;
    }
  }

  {
    BIT<int> bit(N + 200);
    int l = N - 1;
    long long tentou = 0;
    for (int r = N - 1; r >= 0; --r) {
      while (l >= 0) {
        long long add = bit.sum(A[l] - 1);
        // cout << "l: " << l << " add: " << add << endl;
        if (tentou + add <= K) {
          tentou += add;
          bit.add(A[l], 1);
          l -= 1;
        } else {
          break;
        }
      }
      cl[r] = l + 1;
      // cout << "cl[" << r << "] = " << cl[r] << endl;
      // cout << "tentou: " << tentou << endl;
      // A[r]を外す
      long long sub = bit.sum(A[r] + 1, N + 100);
      tentou -= sub;
      bit.add(A[r], -1);
      // cout << "tentou: " << tentou << endl;
    }
  }

  dp[0] = 1;
  dp2[0] = 1;
  for (int r = 0; r < N; ++r) {
    // dp[r+1]の値を求める
    int l = cl[r] - 1;
    dp[r + 1] = dp2[r] - (l >= 0 ? dp2[l] : mint(0));
    dp2[r + 1] = dp2[r] + dp[r + 1];
  }

  cout << dp[N] << endl;
  return 0;
}