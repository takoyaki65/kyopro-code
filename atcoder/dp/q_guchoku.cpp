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
long long dp1[200005], dp2[200005];
int H[200005], A[200005];

// dp[h] := 高さの最大値がhのときのスコア最大値

int main() {
  cin >> N;
  repeat(i, N) cin >> H[i];
  repeat(i, N) cin >> A[i];

  auto *prev = dp1, *next = dp2;
  fill(prev, prev + N + 1, -1LL);
  fill(next, next + N + 1, -1LL);
  prev[0] = 0;
  repeat(i, N) {
    repeat(h, N + 1) {
      // 花iを選ばないとき
      next[h] = prev[h];
    }
    // 花iを選ぶとき
    for (int j = 0; j < H[i]; ++j)
      if (prev[j] != -1)
        next[H[i]] = max(next[H[i]], prev[j] + A[i]);
    swap(prev, next);
  }

  cout << *max_element(prev, prev + N + 1) << endl;
}