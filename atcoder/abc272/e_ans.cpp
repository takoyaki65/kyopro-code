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

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<int> a(n);
  repeat(i, n) scanf("%d", &a[i]);
  vector<vector<int>> vals(m + 1);
  for (int i = 0; i < n; ++i) {
    if (a[i] >= n)
      continue;
    int l = (a[i] >= 0 ? 1 : (-a[i] + i) / (i + 1));
    int r = min(m + 1, (n - a[i] + i) / (i + 1));
    for (int j = l; j < r; ++j) {
      vals[j].push_back(a[i] + (i + 1) * j);
    }
  }
  for (int i = 1; i <= m; ++i) {
    int sz = vals[i].size();
    vector<bool> exi(sz + 1);
    for (auto v : vals[i]) {
      if (v < sz)
        exi[v] = true;
    }
    int res = 0;
    while (exi[res])
      res++;
    printf("%d\n", res);
  }
  return 0;
}