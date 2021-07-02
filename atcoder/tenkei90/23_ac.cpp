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
#include <set>
#include <stack>
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

char str[30][30];
int H, W;

mint dp1[1 << 25], dp2[1 << 25];

int ng[3];

int grid[30][30];

vector<int> states[30];

void init() {
  for (int y = 0; y < W; ++y) {
    memset(grid, 0, sizeof(grid));
    const int gx = 2, gy = y;

    auto rec = [&gx, &gy, &y](auto f, int cx, int cy, int cnt,
                              int bit) -> void {
      if (cnt == W + 1) {
        states[y].push_back(bit);
        return;
      }

      int ToX = cx, ToY = cy - 1;
      if (ToY < 0)
        --ToX, ToY = W - 1;

      // (cx, cy)に0を置く
      f(f, ToX, ToY, cnt + 1, bit);

      // (cx, cy)に1を置く
      for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
          int nx = cx + dx, ny = cy + dy;
          if (nx < 0 || nx >= H || ny < 0 || ny >= W)
            continue;
          if (grid[nx][ny])
            return;
        }
      }

      grid[cx][cy] = 1;
      f(f, ToX, ToY, cnt + 1, bit | (1 << (W - cnt)));
      grid[cx][cy] = 0;
    };

    int sx = gx, sy = gy - 1;
    if (sy < 0)
      --sx, sy = W - 1;

    rec(rec, sx, sy, 0, 0);
  }
}

int main() {
  cin >> H >> W;
  repeat(i, H) cin >> str[i];
  const int maxS = 1 << (W + 1);

  // ng[0] :=
  // 0列目にキングを置くとき、直前(W+1)個のマスで置かれては行けないキングの状態
  // ng[1] := 1 ~ (w-2)列目にキングを置くとき、(同上)
  // ng[2] := (w-1)列目にキングを~(同上)
  ng[0] = (1 << 1) | (1 << 2);
  ng[1] = (1 << 0) | (1 << 1) | (1 << 2) | (1 << W);
  ng[2] = (1 << 0) | (1 << 1) | (1 << W);

  // cout << ng[0] << " " << ng[1] << " " << ng[2] << endl;

  init();

  auto *prev = dp1, *next = dp2;
  prev[0] = 1;
  repeat(i, H) repeat(j, W) {
    for (const int& k : states[(j + 1) % W])
      next[k] = 0;
    // repeat(k, maxS) next[k] = 0;
    int idx = (j == 0) ? 0 : (j == W - 1 ? 2 : 1);
    for (const int& k : states[j]) {
      // repeat(k, maxS) {
      // 駒を置かない
      next[k >> 1] += prev[k];
      // 駒を置く
      if (ng[idx] & k || str[i][j] == '#')
        continue;
      next[(k >> 1) + (1 << W)] += prev[k];
    }
    swap(prev, next);
  }

  mint ans = 0;
  for (const int& k : states[0])
    ans += prev[k];
  cout << ans << endl;

  return 0;
}