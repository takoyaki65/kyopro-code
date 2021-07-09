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

int N, P, K;
long long A[50][50];
long long B[50][50];
const long long INF = 1000000000000LL;

int check(long long X) {
  repeat(i, N) repeat(j, N) B[i][j] = A[i][j];
  repeat(i, N) repeat(j, N) if (B[i][j] == -1) B[i][j] = X;

  repeat(k, N) repeat(i, N) repeat(j, N) B[i][j] =
      min(B[i][j], B[i][k] + B[k][j]);

  int cnt = 0;
  repeat(i, N) repeat_from(j, i + 1, N) if (B[i][j] <= P)++ cnt;

  return cnt;
}

long long upper_bound() {
  long long left = 0, right = INF;
  while (abs(right - left) > 1) {
    long long mid = (left + right) / 2LL;
    int cnt = check(mid);
    if (cnt >= K)
      left = mid;
    else
      right = mid;
  }
  return right;
}

long long lower_bound() {
  long long left = 0, right = INF;
  while (abs(right - left) > 1) {
    long long mid = (left + right) / 2LL;
    int cnt = check(mid);
    if (cnt > K)
      left = mid;
    else
      right = mid;
  }
  return right;
}

int main() {
  cin >> N >> P >> K;
  repeat(i, N) repeat(j, N) cin >> A[i][j];

  long long ub = upper_bound();
  long long lb = lower_bound();
  // cout << "lb: " << lb << endl;
  // cout << "ub: " << ub << endl;

  // (L, R) = (+inf, +inf)のとき、答えは0
  // (L, R) = (x, +inf) (xは有限の値)のとき答えはInfinity
  // この条件を理解してなくてWAしていた

  if (ub == INF && lb != INF) {
    cout << "Infinity" << endl;
    return 0;
  }

  if (ub == INF && lb == INF) {
    cout << 0 << endl;
    return 0;
  }

  long long ans = ub - lb;
  cout << ans << endl;

  return 0;
}