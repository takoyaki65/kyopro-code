// 偶数 = 偶数 + 偶数 or 奇数 + 奇数
// 1. 奇数が2つ以上ある
// 2. 偶数が2つ以上ある
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
  int n;
  scanf("%d", &n);
  vector<int> odds, evens;
  repeat(i, n) {
    int a;
    scanf("%d", &a);
    if (a & 1)
      odds.push_back(a);
    else
      evens.push_back(a);
  }

  int ans = -1;
  if (odds.size() >= 2) {
    sort(odds.rbegin(), odds.rend());
    setmax(ans, odds[0] + odds[1]);
  }
  if (evens.size() >= 2) {
    sort(evens.rbegin(), evens.rend());
    setmax(ans, evens[0] + evens[1]);
  }
  printf("%d\n", ans);
  return 0;
}