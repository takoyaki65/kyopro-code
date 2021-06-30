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

int grid[2002][2002];
int row[2002], col[2002];

int main() {
  int h, w;
  cin >> h >> w;
  repeat(i, h) repeat(j, w) cin >> grid[i][j];

  repeat(i, h) repeat(j, w) {
    row[i] += grid[i][j];
    col[j] += grid[i][j];
  }

  repeat(i, h) {
    repeat(j, w) {
      cout << row[i] + col[j] - grid[i][j] << (j == w - 1 ? "" : " ");
    }
    cout << endl;
  }

  return 0;
}