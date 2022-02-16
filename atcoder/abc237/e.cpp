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
typedef pair<int, int> pii;

void dijkstra(const vector<vector<pii>>& G, int start, vector<long>& dist) {
  const int vsize = G.size();
  dist.assign(vsize, -1);
  priority_queue<pair<long, int>, vector<pair<long, int>>,
                 greater<pair<long, int>>>
      que;
  que.emplace(0, start);
  while (!que.empty()) {
    auto [p, v] = que.top();
    que.pop();
    if (dist[v] != -1)
      continue;
    dist[v] = p;
    for (const auto& [cost, to] : G[v]) {
      if (dist[to] == -1) {
        que.emplace(p + cost, to);
      }
    }
  }
  return;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> H(n);
  for (int i = 0; i < n; ++i)
    cin >> H[i];

  auto graph = vectors(make_pair(0, 0), n, 0);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    if (H[u] < H[v])
      swap(u, v);
    graph[u].emplace_back(0, v);
    graph[v].emplace_back(H[u] - H[v], u);
  }

  vector<long> dist;
  dijkstra(graph, 0, dist);
  for (int i = 0; i < n; ++i) {
    dist[i] = (-dist[i]) - H[i] + H[0];
  }
  cout << *max_element(dist.begin(), dist.end()) << endl;

  return 0;
}