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

// N種類のたこ焼き
// i種類目のたこ焼きの値段はA[i]円
// 合計で1個以上のたこ焼きを買う。
// 同じたこ焼きを複数買うこともできる。
// 支払う金額として有りうるもののうち、安い方からK番目を求める。
// (1 < N <= 10)
// (1 <= A[i] <= 200000)
// (1 <= K <= 1 * 10^9)
int main() {
  int n, k;
  cin >> n >> k;
  k += 1;
  vector<long long> a(n);
  repeat(i, n) cin >> a[i];

  set<long long> q;
  q.insert(0);
  long long ans = -1;
  repeat(i, k) {
    long long ith = *q.begin();
    q.erase(q.begin());
    ans = ith;
    repeat(j, n) {
      q.insert(ith + a[j]);
    }
    // shrink q size to k
    while (q.size() > k) {
      q.erase(--q.end());
    }
  }

  cout << ans << endl;
  return 0;
}