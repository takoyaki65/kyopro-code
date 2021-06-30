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

int main() {
  int n, l, k;
  cin >> n >> l >> k;
  vector<int> va(n + 2);
  for (int i = 1; i <= n; ++i)
    cin >> va[i];
  va[0] = 0, va[n + 1] = l;

  auto test = [&va, &n, &l, &k](int minL) -> bool {
    int len = 0, num = 0;
    for (int i = 0; i <= n; ++i) {
      len += va[i + 1] - va[i];
      if (len >= minL)
        len = 0, ++num;
    }
    return num >= k + 1;
  };

  int ok = 0, ng = l + 10000;
  while (abs(ok - ng) > 1) {
    int mid = (ok + ng) / 2;
    // cout << ok << ", " << mid << ", " << ng;
    if (test(mid))
      ok = mid;
    else
      ng = mid;
    // cout << " -> " << ok << ", " << mid << ", " << ng << endl;
  }
  cout << ok << endl;

  return 0;
}