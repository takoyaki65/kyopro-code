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

using pii = pair<int, int>;
using Edge_type = pair<int, int>;
using Vertex_type = vector<Edge_type>;
using Graph_type = vector<Vertex_type>;

int N, M;
Vertex_type graph[100001];
int dist_from0[100001];
int dist_fromN[100001];

void dijkstra(int s, int* dist) {
  memset(dist, -1, N * sizeof(int));
  priority_queue<pii, vector<pii>, greater<pii>> que;
  que.push({0, s});
  while (!que.empty()) {
    auto [d, v] = que.top();
    que.pop();
    if (dist[v] != -1)
      continue;
    dist[v] = d;
    for (const auto& [to, cost] : graph[v]) {
      if (dist[to] == -1)
        que.push({d + cost, to});
    }
  }
  return;
}

int main() {
  cin >> N >> M;
  repeat(i, M) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
  }

  dijkstra(0, dist_from0);
  dijkstra(N - 1, dist_fromN);

  repeat(i, N) { cout << dist_from0[i] + dist_fromN[i] << endl; }

  return 0;
}