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
// dp[l][r] := 区間[0, r)を合体させるための最小コスト
long long dp[402][402];
long long A[402];
// acum[r] = [0, r)までのAの累積和
long long acum[102];

const long long INF = numeric_limits<long long>::max();

int main() {
  cin >> N;
  repeat(i, N) cin >> A[i];
  acum[0] = 0;
  repeat(i, N) acum[i + 1] = acum[i] + A[i];

  for (int w = 2; w <= N; ++w) {
    for (int l = 0; l + w <= N; ++l) {
      int r = l + w;
      long long val = INF;
      long long cost = acum[r] - acum[l];
      for (int k = l + 1; k < r; ++k) {
        val = min(val, cost + dp[l][k] + dp[k][r]);
      }
      dp[l][r] = val;
    }
  }

  cout << dp[0][N] << endl;
  return 0;
}