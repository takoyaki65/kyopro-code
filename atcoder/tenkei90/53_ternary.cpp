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

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    int lc = 1, rc = N;
    // lc, lc + 1, lc + 2
    while (lc + 2 < rc) {
      int c1 = lc + (rc - lc) / 3;
      int c2 = rc - (rc - lc) / 3;
      int f1, f2;
      cout << "? " << c1 << endl;
      cin >> f1;
      cout << "? " << c2 << endl;
      cin >> f2;
      if (f1 < f2) {
        lc = c1;
      } else {
        // f1 >= f2
        rc = c2;
      }
    }
    int ans = 0, fv;
    cout << "? " << lc << endl;
    cin >> fv;
    ans = max(ans, fv);
    if (lc + 1 <= rc) {
      cout << "? " << lc + 1 << endl;
      cin >> fv;
      ans = max(ans, fv);
    }
    if (lc + 2 <= rc) {
      cout << "? " << rc << endl;
      cin >> fv;
      ans = max(ans, fv);
    }
    cout << "! " << ans << endl;
  }
  return 0;
}