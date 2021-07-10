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

int H, W;
char grid[30][30];
int sx, sy;
bool visit[30][30];
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
int rec(int x, int y, int d) {
  if (x == sx && y == sy)
    return d;
  int ret = -1;
  for (int k = 0; k < 4; ++k) {
    int nx = x + dx[k], ny = y + dy[k];
    if (nx < 0 || nx >= H || ny < 0 || ny >= W || grid[nx][ny] == '#')
      continue;
    if (!visit[nx][ny]) {
      visit[nx][ny] = true;
      ret = max(ret, rec(nx, ny, d + 1));
      visit[nx][ny] = false;
    }
  }
  return ret;
}

int solve(int x, int y) {
  if (grid[x][y] == '#')
    return -1;
  sx = x, sy = y;
  int ret = -1;
  for (int k = 0; k < 4; ++k) {
    int nx = x + dx[k], ny = y + dy[k];
    if (nx < 0 || nx >= H || ny < 0 || ny >= W || grid[nx][ny] == '#')
      continue;
    visit[nx][ny] = true;
    ret = max(ret, rec(nx, ny, 1));
    visit[nx][ny] = false;
  }
  return ret;
}

int main() {
  cin >> H >> W;
  repeat(i, H) cin >> grid[i];

  int ans = -1;
  for (int x = 0; x < H; ++x) {
    for (int y = 0; y < W; ++y) {
      memset(visit, 0, sizeof(visit));
      ans = max(ans, solve(x, y));
    }
  }

  if (ans <= 2) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }

  return 0;
}