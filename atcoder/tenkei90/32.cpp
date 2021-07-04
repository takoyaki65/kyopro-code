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

int N, M;
int A[12][12];
int G[12][12];
int dp[12][12][1 << 11];

const int INF = 1000000000;

int rec(int idx, int bit, int prev) {
  if (idx == N) {
    assert(bit == 0);
    return 0;
  }
  if (prev != -1 && dp[idx][prev][bit] != -1) {
    return dp[idx][prev][bit];
  }

  int ret = INF;
  for (int i = 0; i < N; ++i) {
    if (((prev != -1 && G[prev][i] == 1) || (prev == -1)) && ((bit >> i) & 1)) {
      ret = min(ret, A[i][idx] + rec(idx + 1, bit & ~(1 << i), i));
    }
  }

  if (prev == -1)
    return ret;
  return dp[idx][prev][bit] = ret;
}

int main() {
  cin >> N;
  repeat(i, N) repeat(j, N) cin >> A[i][j];
  cin >> M;
  repeat(i, N) repeat(j, N) G[i][j] = 1;
  repeat(i, M) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    G[x][y] = G[y][x] = 0;
  }
  memset(dp, -1, sizeof(dp));

  int ans = rec(0, (1 << N) - 1, -1);
  if (ans == INF)
    cout << -1 << endl;
  else
    cout << ans << endl;

  return 0;
}