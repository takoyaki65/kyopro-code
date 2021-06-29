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

const int INF = 1000000000;
using edge_type = pair<int, int>;
using edgeList_type = vector<edge_type>;
using Graph_type = vector<edgeList_type>;

void dijkstra(const Graph_type& G, int start, vector<int>& dist) {
  priority_queue<edge_type, vector<edge_type>, greater<edge_type>> que;
  const int n = G.size();
  dist.assign(n, -1);
  que.push({0, start});
  while (!que.empty()) {
    auto [d, v] = que.top();
    que.pop();
    if (dist[v] != -1)
      continue;
    dist[v] = d;
    for (const auto& [cost, to] : G[v]) {
      if (dist[to] == -1) {
        que.push({d + cost, to});
      }
    }
  }
  return;
}

int main() {
  int n, m;
  cin >> n >> m;
  Graph_type G(n);
  repeat(i, m) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    G[a].push_back({c, b});
  }

  auto Dtable = vectors(-1, n, n);
  repeat(i, n) { dijkstra(G, i, Dtable[i]); }

  repeat(i, n) {
    int ans = INF;
    // i -> iのエッジ -> i
    for (const auto& [cost, to] : G[i]) {
      if (to == i) {
        ans = min(ans, cost);
      }
    }
    repeat(j, n) if (i != j && Dtable[i][j] != -1 && Dtable[j][i] != -1) {
      ans = min(ans, Dtable[i][j] + Dtable[j][i]);
    }

    cout << (ans == INF ? -1 : ans) << endl;
  }

  return 0;
}