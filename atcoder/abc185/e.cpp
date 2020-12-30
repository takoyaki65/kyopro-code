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

// dp[i][j] := Aを[0, i),Bを[0, j)まで見たときの答え
// dp[0][0] = 0

int main() {
  int n{0}, m{0};
  cin >> n >> m;
  vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int j = 0; j < m; ++j) cin >> b[j];
  const int INF = 1e9;
  auto dp = vectors(INF, n + 1, m + 1);

  dp[0][0] = 0;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i > 0) setmin(dp[i][j], dp[i - 1][j] + 1);
      if (j > 0) setmin(dp[i][j], dp[i][j - 1] + 1);
      if (i > 0 and j > 0)
        setmin(dp[i][j], dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
    }
  }
  cout << dp[n][m] << endl;
  return 0;
}