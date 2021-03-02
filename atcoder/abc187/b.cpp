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

// -1 <= (y_j - y_i)/(x_j - x_i) <= 1
// x_j - x_i > 0のとき
// -(x_j - x_i) <= y_j - y_i <= x_j - x_i
// x_j - x_i < 0のとき
// (x_j - x_i) <= y_j - y_i <= -(x_j - x_i)

int main() {
  int n;
  cin >> n;
  int x[n], y[n];
  repeat(i, n) cin >> x[i] >> y[i];

  int ans = 0;
  auto match = [](int xi, int yi, int xj, int yj) -> bool {
    if (xi < xj) {
      bool f1 = -(xj - xi) <= (yj - yi);
      bool f2 = (yj - yi) <= (xj - xi);
      return f1 && f2;
    } else {
      bool f1 = (xj - xi) <= (yj - yi);
      bool f2 = (yj - yi) <= -(xj - xi);
      return f1 && f2;
    }
  };
  repeat(i, n) {
    repeat_from(j, i + 1, n) {
      if (match(x[i], y[i], x[j], y[j])) ++ans;
    }
  }
  cout << ans << endl;
  return 0;
}