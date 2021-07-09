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

int Ask(int idx) {
  cout << "? " << idx << endl;
  int fv;
  cin >> fv;
  return fv;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    if (N == 1) {
      int v = Ask(1);
      cout << "! " << v << endl;
      continue;
    }
    int lc = 1, rc = N;
    int ans = 0;
    for (int i = 0; i < 11; ++i) {
      int mid = (lc + rc) / 2;
      int v1 = Ask(mid);
      int v2 = Ask(mid + 1);
      int fv = v2 - v1;
      if (fv > 0)
        lc = mid;
      else
        rc = mid;
      ans = max({ans, v1, v2});
    }
    cout << "! " << ans << endl;
  }
  return 0;
}