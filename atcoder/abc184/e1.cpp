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

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
const int INF = 1000000000;

int dijkstra(const vector<vector<pair<int, int>>> &graph, const int s,
             const int g) {
  const int v_size = graph.size();
  vector<int> dist(v_size, INF);
  dist[s] = 0;
  deque<int> deq;
  deq.push_back(s);
  while (!deq.empty()) {
    int v = deq.front();
    deq.pop_front();
    for (auto [nv, cost] : graph[v]) {
      if (dist[nv] > dist[v] + cost) {
        dist[nv] = dist[v] + cost;
        if (cost)
          deq.push_back(nv);
        else
          deq.push_front(nv);
      }
    }
  }

  return dist[g];
}

int main() {
  int height, width;
  cin >> height >> width;
  vector<string> grid(height);
  repeat(i, height) cin >> grid[i];

  int sx = 0, sy = 0, gx = 0, gy = 0;
  repeat(i, height) {
    repeat(j, width) {
      if (grid[i][j] == '#') continue;
      if (grid[i][j] == 'S') {
        sy = i, sx = j;
      } else if (grid[i][j] == 'G') {
        gy = i, gx = j;
      }
    }
  }

  const int az_num = 'z' - 'a' + 1;
  const int v_num = height * width;
  const int g_size = v_num + az_num;
  const int s_id = sy * width + sx;
  const int g_id = gy * width + gx;
  // cout << "g_size: " << g_size << endl;
  assert(s_id < g_size and g_id < g_size);
  auto graph = vectors(pair<int, int>(), g_size, 0);
  repeat(y, height) {
    repeat(x, width) {
      if (grid[y][x] == '#') continue;
      int v_id = y * width + x;
      assert(v_id < g_size);
      repeat(i, 4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 or ny >= height or nx < 0 or nx >= width) continue;
        if (grid[ny][nx] == '#') continue;
        int nv_id = ny * width + nx;
        assert(nv_id < g_size);
        graph[v_id].emplace_back(nv_id, 1);
        // graph[nv_id].emplace_back(v_id, 1);
      }
      if (islower(grid[y][x])) {
        int nv_id = v_num + (grid[y][x] - 'a');
        assert(nv_id < g_size);
        graph[v_id].emplace_back(nv_id, 0);
        graph[nv_id].emplace_back(v_id, 1);
      }
    }
  }
  /*
    repeat(i, g_size) {
      for (auto [v, cost] : graph[i]) {
        cout << "(" << v << " , " << cost << ") ";
      }
      cout << endl;
    }
   */
  int res = dijkstra(graph, s_id, g_id);
  if (res == INF) {
    res = -1;
  }
  cout << res << endl;
  return 0;
}