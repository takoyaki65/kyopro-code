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

using ll = long long;
ll dist[1 << 16];
ll dp[16][1 << 16];
int N, K;
ll X[16], Y[16];

int main() {
  cin >> N >> K;
  repeat(i, N) cin >> X[i] >> Y[i];
  // dist[bit] := グループbit内の点群の、距離の最大値
  {
    ll tx[16], ty[16];
    int cnt = 0;
    for (int i = 1; i < (1 << N); ++i) {
      cnt = 0;
      for (int j = 0; j < N; ++j) {
        if ((i >> j) & 1) {
          tx[cnt] = X[j], ty[cnt] = Y[j];
          cnt += 1;
        }
      }

      ll val = 0;
      for (int j = 0; j < cnt; ++j) {
        for (int k = j + 1; k < cnt; ++k) {
          val = max(val, (tx[j] - tx[k]) * (tx[j] - tx[k]) +
                             (ty[j] - ty[k]) * (ty[j] - ty[k]));
        }
      }
      dist[i] = val;
    }
  }

  // dp[k][bit] := すでにあるグループ数k と すでに選んだ点群bit に対して
  //               グループごとの最大距離 の最小値
  // 初期値
  for (int bit = 1; bit < (1 << N); ++bit) {
    dp[1][bit] = dist[bit];
  }

  const ll inf = numeric_limits<ll>::max();
  // 遷移
  for (int k = 2; k <= K; ++k) {
    for (int bit = 1; bit < (1 << N); ++bit) {
      dp[k][bit] = inf;
      // https://ark4rk.hatenablog.com/entry/2018/03/07/230257
      for (int S = (bit - 1) & bit; S != 0; S = (S - 1) & bit) {
        dp[k][bit] = min(dp[k][bit], max(dp[k - 1][bit - S], dist[S]));
      }
    }
  }

  cout << dp[K][(1 << N) - 1] << endl;
  return 0;
}