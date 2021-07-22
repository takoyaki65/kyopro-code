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

// プログラミングコンテストチャレンジブック
// 第2版 304ページ
// K-Anonymous Sequence
using ll = long long;
int N;
ll C;
ll h[200005];
ll dp[200005];
int deq[200005];

ll f(int j, int i) {
  ll aj = -2LL * h[j];
  ll bj = dp[j] + h[j] * h[j];
  return aj * h[i] + bj;
}

bool check(int f1, int f2, int f3) {
  ll a1 = -2LL * h[f1], b1 = dp[f1] + h[f1] * h[f1];
  ll a2 = -2LL * h[f2], b2 = dp[f2] + h[f2] * h[f2];
  ll a3 = -2LL * h[f3], b3 = dp[f3] + h[f3] * h[f3];
  return (b3 - b2) * (a2 - a1) >= (a3 - a2) * (b2 - b1);
}

int main() {
  cin >> N >> C;
  repeat(i, N) cin >> h[i];

  dp[0] = 0;
  int s = 0, t = 1;
  for (int i = 1; i < N; ++i) {
    while (s + 1 < t && f(deq[s], i) >= f(deq[s + 1], i))
      s += 1;
    dp[i] = h[i] * h[i] + C + f(deq[s], i);
    // 直線iを追加、不要な直線を末尾から取っていく
    while (s + 1 < t && check(deq[t - 2], deq[t - 1], i))
      t -= 1;
    deq[t++] = i;
  }

  cout << dp[N - 1] << endl;

  return 0;
}