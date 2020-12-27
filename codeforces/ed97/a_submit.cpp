#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T &x) {
  return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T &a, T b) {
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

// a*k + ceil(a/2) ~ a*k + a - 1
// である必要がある．
// a > (x mod a) >= ceil(a/2)

// a = 1  :   1 > 0 >= 1  : ×
// a = 2  :   2 > (0 or 1)  >= 1  : x mod a == 1である必要がある
// a = 3  :   3 > (0 ~ 2) >= 2    : x mod a == 2である必要がある
// a = 10 :  10 > (0 ~ 9) >= 5    : x mod a = 5 ~ 9である必要がある

int main() {
  int t;
  cin >> t;
  while (t--) {
    int l, r;
    cin >> l >> r;
  }
  return 0;
}