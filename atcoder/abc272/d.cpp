#include <algorithm>
#include <array>
#include <bitset>
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
#define bit_stand(n, k) ((n >> k) & 1)
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

int grid[410][410];
int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<pair<int, int>> dv;
  repeat(i, n) {
    repeat(j, n) {
      if (i * i + j * j == m) {
        dv.push_back({+i, +j});
        dv.push_back({+i, -j});
        dv.push_back({-i, +j});
        dv.push_back({-i, -j});
      }
    }
  }

  // for (const auto [dx, dy] : dv) {
  //   printf("{%d %d}\n", dx, dy);
  // }

  memset(grid, -1, sizeof(grid));
  queue<tuple<int, int, int>> que;
  que.push({1, 1, 0});
  while (!que.empty()) {
    auto [x, y, c] = que.front();
    que.pop();
    if (grid[x][y] != -1)
      continue;
    grid[x][y] = c;
    for (const auto& [dx, dy] : dv) {
      int nx = x + dx, ny = y + dy;
      if (nx < 1 || nx > n || ny < 1 || ny > n || grid[nx][ny] != -1)
        continue;
      que.push({nx, ny, c + 1});
    }
  }

  repeat_from(i, 1, n + 1) {
    repeat_from(j, 1, n + 1) {
      printf("%d%c", grid[i][j], (j == n ? '\n' : ' '));
    }
  }

  return 0;
}