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

int N;
int A[402];
// dp[l][r] := [l,r)の区間の人が全て抜ける場合の最小コスト
int dp[402][402];

int main() {
  cin >> N;
  repeat(i, 2 * N) cin >> A[i];

  repeat(i, 2 * N + 1) repeat(j, 2 * N + 1) dp[i][j] = 1000000000;

  for (int i = 0; i + 2 <= 2 * N; ++i) {
    dp[i][i + 2] = abs(A[i + 1] - A[i]);
  }

  for (int w = 4; w <= 2 * N; w += 2) {
    for (int i = 0; i + w <= 2 * N; ++i) {
      // dp[i][i+w]を求める
      // 1. 区間[i+1, i+w-1)が全て抜けて(i), (i+w-1)が最後に抜ける場合
      dp[i][i + w] = dp[i + 1][i + w - 1] + abs(A[i] - A[i + w - 1]);
      for (int j = 2; j < w; j += 2) {
        // 2. 区間[i, i+j), 区間[i+j, i+w)が別々に抜ける場合
        dp[i][i + w] = min(dp[i][i + w], dp[i][i + j] + dp[i + j][i + w]);
      }
    }
  }

  cout << dp[0][2 * N] << endl;

  return 0;
}