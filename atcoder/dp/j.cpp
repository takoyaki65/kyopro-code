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

int N;
// dp[i][j][k] := 寿司1個の皿がi皿,2個がj皿,3個がk皿
//                の状態から全て0皿にするまでの操作回数の期待値
double dp[302][302][302];

double rec(int i, int j, int k) {
  if (i < 0 || i > N || j < 0 || j > N || k < 0 || k > N)
    return 0.0;
  if (dp[i][j][k] >= 0)
    return dp[i][j][k];
  return dp[i][j][k] = (rec(i - 1, j, k) * i + rec(i + 1, j - 1, k) * j +
                        rec(i, j + 1, k - 1) * k + N) /
                       (i + j + k);
}

int main() {
  cin >> N;
  int cnt[4] = {0, 0, 0, 0};
  repeat(i, N) {
    int a;
    cin >> a;
    cnt[a] += 1;
  }
  repeat(i, N + 1) repeat(j, N + 1) repeat(k, N + 1) dp[i][j][k] = -1;

  dp[0][0][0] = 0;

  cout << fixed << setprecision(10) << rec(cnt[1], cnt[2], cnt[3]) << endl;

  return 0;
}