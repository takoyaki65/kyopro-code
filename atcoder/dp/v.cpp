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

int N;
vector<int> g[100005];
// dp[v] := 頂点vを黒にしたとき、頂点vの部分木で条件を満たす塗り方
mint dp[100005];
mint ans[100005];

void rec1(int v, int par) {
  dp[v] = 1;
  for (const int& to : g[v]) {
    if (to == par)
      continue;
    rec1(to, v);
    // vの子をc1, c2, ... c_pとして
    // dp[v] = (dp[c1] + 1) * (dp[c2] + 1) * ... * (dp[c_p] + 1)
    // 1はc1が白に塗られているとき(c1の部分木はすべて白に塗られるので1通り)
    dp[v] *= dp[to] + 1;
  }
}

void rec2(int v, mint d_par, int par) {
  const int n = g[v].size();
  vector<mint> lht(n, mint(1)), rht(n, mint(1));
  repeat(i, n) {
    int to = g[v][i];
    if (to == par)
      lht[i] = rht[i] = d_par + 1;
    else
      lht[i] = rht[i] = dp[to] + 1;
  }
  repeat_from(i, 1, n) lht[i] *= lht[i - 1];
  for (int i = n - 2; i >= 0; --i)
    rht[i] *= rht[i + 1];

  ans[v] = n ? lht[n - 1] : 1;

  repeat(i, n) {
    int to = g[v][i];
    if (par == to)
      continue;
    mint next_d_par = 1;
    if (i)
      next_d_par *= lht[i - 1];
    if (i + 1 < n)
      next_d_par *= rht[i + 1];
    rec2(to, next_d_par, v);
  }
}

int main() {
  cin >> N >> MOD;
  repeat(i, N - 1) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  rec1(0, -1);
  rec2(0, 0, -1);
  for (int i = 0; i < N; ++i) {
    cout << ans[i] << endl;
  }

  return 0;
}