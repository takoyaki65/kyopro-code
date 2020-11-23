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

int main() {
  int gold, silver, cupper;
  cin >> gold >> silver >> cupper;
  auto dp = vectors(-1.0, 101, 101, 101);
  auto rec = [&](auto f, int g, int s, int c) -> double {
    if (dp[g][s][c] >= -0.5) {
      return dp[g][s][c];
    }
    if (g >= 100 or s >= 100 or c >= 100) {
      return dp[g][s][c] = 0.0;
    }

    double tot = g + s + c;
    double ret = g / tot * (f(f, g + 1, s, c) + 1) +
                 s / tot * (f(f, g, s + 1, c) + 1) +
                 c / tot * (f(f, g, s, c + 1) + 1);
    return dp[g][s][c] = ret;
  };
  cout << fixed << setprecision(10) << rec(rec, gold, silver, cupper) << endl;
  return 0;
}