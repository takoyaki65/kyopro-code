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

using ti4 = tuple<int, int, int, int>;
int H, W;
int sx, sy, gx, gy;
char grid[1010][1010];
// dp[x][y][dir] = changeDirCnt
int dp[1010][1010][4];

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int main() {
  cin >> H >> W >> sx >> sy >> gx >> gy;
  repeat(i, H) cin >> grid[i];
  --sx, --sy, --gx, --gy;

  memset(dp, -1, sizeof(dp));
  // 01BFS
  // [changeDirCnt, x, y, dir]
  deque<ti4> que;
  que.push_back({0, sx, sy, 0});
  que.push_back({0, sx, sy, 1});
  que.push_back({0, sx, sy, 2});
  que.push_back({0, sx, sy, 3});

  while (!que.empty()) {
    auto [changeDirCnt, cx, cy, dir] = que.front();
    que.pop_front();
    if (dp[cx][cy][dir] != -1)
      continue;
    dp[cx][cy][dir] = changeDirCnt;
    for (int k = 0; k < 4; ++k) {
      int nx = cx + dx[k], ny = cy + dy[k];
      if (nx < 0 || nx >= H || ny < 0 || ny >= W || grid[nx][ny] == '#')
        continue;
      if (dir == k)
        que.push_front({changeDirCnt, nx, ny, k});
      else
        que.push_back({changeDirCnt + 1, nx, ny, k});
    }
  }

  int ans = 1000000000;
  for (int k = 0; k < 4; ++k) {
    if (dp[gx][gy][k] != -1)
      ans = min(ans, dp[gx][gy][k]);
  }

  cout << ans << endl;

  return 0;
}