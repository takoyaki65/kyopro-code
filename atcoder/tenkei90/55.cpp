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
long long A[110];
long long P, Q;

int rec(int idx, int cnt, long long val) {
  if (idx == N) {
    return (cnt == 5 && val == Q) ? 1 : 0;
  }
  if (cnt == 5) {
    return (val == Q) ? 1 : 0;
  }
  // remain = N - idx;
  // 残り5 - cnt個選ぶ必要がある
  // remain < 5 - cntの場合、打ち切り
  if (N - idx < 5 - cnt)
    return 0;

  int ret = 0;
  // idx番目を選ばない
  ret += rec(idx + 1, cnt, val);
  // idx番目を選ぶ
  ret += rec(idx + 1, cnt + 1, val * A[idx] % P);
  return ret;
}

int main() {
  cin >> N >> P >> Q;
  repeat(i, N) cin >> A[i];
  int ans = rec(0, 0, 1);
  cout << ans << endl;
  return 0;
}