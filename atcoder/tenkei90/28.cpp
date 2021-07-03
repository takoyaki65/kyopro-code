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

int N;
// grid[x][y] := [x, x+1), [y, y+1)の領域に重なっている紙の枚数
int grid[1100][1100];
int ans[100005];

int main() {
  cin >> N;
  repeat(i, N) {
    int lx, ly, rx, ry;
    cin >> lx >> ly >> rx >> ry;
    grid[lx][ly] += 1;
    grid[rx][ly] += -1;
    grid[lx][ry] += -1;
    grid[rx][ry] += 1;
  }

  repeat(x, 1100) repeat_from(y, 1, 1100) grid[x][y] += grid[x][y - 1];

  repeat(y, 1100) repeat_from(x, 1, 1100) grid[x][y] += grid[x - 1][y];

  repeat(x, 1100) repeat(y, 1100)++ ans[grid[x][y]];

  repeat_from(i, 1, N + 1) cout << ans[i] << endl;

  return 0;
}