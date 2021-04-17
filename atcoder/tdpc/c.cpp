#include <algorithm>
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

// 解説 https://compro.tsutaj.com//archive/180220_probability_dp.pdf
// 10ページ～参照
int N, K, R[1050];
double dp[1050][15];

int main() {
  scanf("%d", &K);
  N = 1 << K;
  for (int i = 0; i < N; ++i) {
    scanf("%d", &R[i]);
    dp[i][0] = 1.0;
  }
  for (int k = 1; k <= K; ++k) {
    for (int i = 0; i < N; ++i) {
      // マッチする可能性のある選手の下限(自分が上ったトーナメント下も含む)
      int lb = (i >> k) << k;
      for (int j = lb; j < lb + (1 << k); ++j) {
        // 自分が上がってきたトーナメント下の選手なら、計算に加味しない
        if ((i >> (k - 1) & 1) == (j >> (k - 1) & 1))
          continue;

        double prob_match = dp[i][k - 1] * dp[j][k - 1];
        double prob_win = 1.0 / (1 + pow(10.0, (R[j] - R[i]) / 400.0));
        dp[i][k] += prob_match * prob_win;
      }
    }
  }
  for (int i = 0; i < N; ++i)
    printf("%.12f\n", dp[i][K]);
  return 0;
}