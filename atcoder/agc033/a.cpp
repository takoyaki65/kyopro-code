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

using ll = long long;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int main() {
  int h{0}, w{0};
  cin >> h >> w;
  vector<string> grid(h);
  repeat(i, h) cin >> grid[i];
  set<pair<int, int>> prv, nxt;
  repeat(i, h) {
    repeat(j, w) {
      if (grid[i][j] == '#') prv.emplace(i, j);
    }
  }
  int ans = 0;
  while (!prv.empty()) {
    nxt.clear();
    for (auto [y, x] : prv) {
      for (int i = 0; i < 4; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny < 0 or ny >= h or nx < 0 or nx >= w or grid[ny][nx] == '#') {
          continue;
        }
        grid[ny][nx] = '#';
        nxt.emplace(ny, nx);
      }
    }
    swap(prv, nxt);
    if (prv.empty()) break;
    ++ans;
  }
  cout << ans << endl;
  return 0;
}