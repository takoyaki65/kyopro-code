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

struct block {
  int w, s, v;
  bool operator<(const block& rhs) const { return w + s < rhs.w + rhs.s; }
};

int N;
// dp[i+1][j] := i番目までのブロックを使って、
//               重さの総量がjのときの価値の最大値
long long dp[1001][40001];
block blk[1002];

int main() {
  cin >> N;
  repeat(i, N) {
    int w, s, v;
    cin >> w >> s >> v;
    blk[i] = {w, s, v};
  }
  sort(blk, blk + N);

  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0;

  repeat(i, N) {
    auto [w, s, v] = blk[i];
    repeat(j, 20002) {
      // cout << "i+1: " << i + 1 << " j: " << j << endl;
      // blk[i]を使わない場合
      dp[i + 1][j] = dp[i][j];
      // blk[i]を使う場合
      if (j - w >= 0 && j - w <= s && dp[i][j - w] != -1) {
        dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - w] + v);
      }
    }
  }
  long long ans = *max_element(dp[N], dp[N] + 20002);
  cout << ans << endl;
  return 0;
}