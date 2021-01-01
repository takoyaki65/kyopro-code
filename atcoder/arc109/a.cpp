#include <bits/stdc++.h>
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

template <typename T>
using V = vector<T>;

template <typename T>
using VV = V<V<T>>;

int dijkstra(const VV<pair<int, int>> &graph, const int s, const int g) {
  const int INF = 1e9;
  const int v = graph.size();
  vector<int> res(v, INF);

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      que;

  que.emplace(0, s);
  while (!que.empty()) {
    const auto [d, cur] = que.top();
    // cout << "d: " << d << "cur: " << cur << endl;
    que.pop();
    if (res[cur] <= d) continue;
    res[cur] = d;
    for (const auto &[to, cost] : graph[cur]) {
      que.emplace(d + cost, to);
    }
  }

  return res[g];
}

int main() {
  int a{0}, b{0}, x{0}, y{0};
  cin >> a >> b >> x >> y;
  a = a - 1;
  b = b - 1 + 100;
  const int v = 200;
  const int an = 100, bn = 100;
  auto g = vectors(pair<int, int>(), v, 0);

  repeat(i, 100) {
    g[i].emplace_back(i + 100, x);
    g[i + 100].emplace_back(i, x);
  }
  repeat(i, 99) {
    g[i + 1].emplace_back(i + 100, x);
    g[i + 100].emplace_back(i + 1, x);
  }

  repeat(i, 99) {
    g[i].emplace_back(i + 1, y);
    g[i + 1].emplace_back(i, y);
    g[i + 100].emplace_back(i + 101, y);
    g[i + 101].emplace_back(i + 100, y);
  }
  cout << dijkstra(g, a, b) << endl;
  return 0;
}