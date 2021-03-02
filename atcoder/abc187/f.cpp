#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
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
inline int sz(T &x) {
  return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T &a, T b) {
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

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> g(n);
  repeat(i, m) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    g[a] |= 1 << b;
    g[b] |= 1 << a;
  }

  const int INF = 1 << 30;
  vector<int> dp(1 << n, INF);
  dp[0] = 1;
  for (int j = 0; j < 1 << n; ++j) {
    for (int i = 0; i < n; ++i) {
      if (dp[j] == 1 && (g[i] & j) == j) dp[j | 1 << i] = 1;
    }
  }
  for (int i = 1; i < 1 << n; ++i) {
    int j = i;
    do {
      dp[i] = min(dp[i], dp[i ^ j] + dp[j]);

      // j := iの部分集合
      // 部分集合の求め方についての解説
      // https://ark4rk.hatenablog.com/entry/2018/03/07/230257
      j = (j - 1) & i;
    } while (j > 0);
  }
  cout << dp[(1 << n) - 1] << endl;

  return 0;
}