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

int N;
int A[20][20];
// dp[S] := 集合Sをグループ分けするときの最高得点
long long dp[(1 << 16) + 100];

long long rec(int S) {
  if (S == 0)
    return 0;
  if (dp[S] != -1)
    return dp[S];

  long long ret = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if ((S >> i) & 1 && (S >> j) & 1) {
        ret += A[i][j];
      }
    }
  }

  for (int T = (S - 1) & S; T > 0; T = (T - 1) & S) {
    ret = max(ret, rec(S & (~T)) + rec(T));
  }
  return dp[S] = ret;
}

int main() {
  cin >> N;
  repeat(i, N) repeat(j, N) cin >> A[i][j];
  memset(dp, -1, sizeof(dp));

  cout << rec((1 << N) - 1) << endl;
}