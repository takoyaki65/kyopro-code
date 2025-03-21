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
  long long sx, sy, gx, gy;
  cin >> sx >> sy >> gx >> gy;
  if (sx == gx and sy == gy) {
    cout << 0 << endl;
    return 0;
  }

  if ((sx - sy == gx - gy) or (sx + sy == gx + gy) or
      abs(sx - gx) + abs(sy - gy) <= 3) {
    cout << 1 << endl;
    return 0;
  }

  if ((sx + sy + gx + gy) % 2 == 0) {
    cout << 2 << endl;
    return 0;
  }

  if (abs(sx - gx) + abs(sy - gy) <= 6) {
    cout << 2 << endl;
    return 0;
  }

  if (abs((sx + sy) - (gx + gy)) <= 3) {
    cout << 2 << endl;
    return 0;
  }

  if (abs((sx - sy) - (gx - gy)) <= 3) {
    cout << 2 << endl;
    return 0;
  }
  cout << 3 << endl;
  return 0;
}