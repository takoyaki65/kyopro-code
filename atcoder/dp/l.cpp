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
int A[3010];
// dp[k][l][r] := 残っているdequeが区間[l,r)で、
//                現在、太郎君のターン(k=0)または次郎君のターン(k=1)のとき、
//                そこからゲームを始めたときの最終的なX-Yの値
long long dp[2][3010][3010];

long long rec(int k, int l, int r) {
  if (l == r)
    return 0;
  if (dp[k][l][r] != -1)
    return dp[k][l][r];

  long long ret = 0;
  if (k == 0) {
    // 太郎君のターン(得点差を最大化)
    ret = max({rec(1 - k, l + 1, r) + A[l], rec(1 - k, l, r - 1) + A[r - 1]});
  } else {
    // 次郎君のターン(得点差を最小化)
    ret = min({rec(1 - k, l + 1, r) - A[l], rec(1 - k, l, r - 1) - A[r - 1]});
  }
  return dp[k][l][r] = ret;
}

int main() {
  cin >> N;
  repeat(i, N) cin >> A[i];

  memset(dp, -1, sizeof(dp));

  cout << rec(0, 0, N) << endl;

  return 0;
}