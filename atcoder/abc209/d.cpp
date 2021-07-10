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

struct Edge {
  long long to;
};
using Graph = vector<vector<Edge>>;

/*
 * LCA(G, root): 木Gに対する根をrootとして Lowest Common Ancestor を求める構造体
 * query(u,v): u と v の LCA を求める。計算量O(logn)
 * 前処理: O(nlogn)時間
 */
struct LCA {
  vector<vector<int>> parent;  // parent[k][u]:= uの2^k先の親
  vector<int> dist;            // rootからの距離
  LCA(const Graph& G, int root = 0) { init(G, root); }

  // 初期化
  void init(const Graph& G, int root) {
    int V = G.size();
    int K = 1;
    while ((1 << K) < V)
      K++;
    parent.assign(K, vector<int>(V, -1));
    dist.assign(V, -1);
    dfs(G, root, -1, 0);
    for (int k = 0; k + 1 < K; ++k) {
      for (int v = 0; v < V; ++v) {
        if (parent[k][v] < 0) {
          parent[k + 1][v] = -1;
        } else {
          parent[k + 1][v] = parent[k][parent[k][v]];
        }
      }
    }
  }

  // 根からの距離と1つ先の頂点を求める
  void dfs(const Graph& G, int v, int p, int d) {
    parent[0][v] = p;
    dist[v] = d;
    for (auto e : G[v]) {
      if (e.to != p)
        dfs(G, e.to, v, d + 1);
    }
  }

  // u と v のLCAを求める
  int query(int u, int v) {
    // uの方が深いとする
    if (dist[u] < dist[v])
      swap(u, v);

    int K = parent.size();
    // LCAまでの距離を同じにする
    for (int k = 0; k < K; ++k) {
      if ((dist[u] - dist[v]) >> k & 1) {
        u = parent[k][u];
      }
    }

    // 2分探索でLCAを求める
    if (u == v)
      return u;
    for (int k = K - 1; k >= 0; --k) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }

  // 頂点u と v の距離を求める
  int length(int u, int v) { return dist[u] + dist[v] - 2 * dist[query(u, v)]; }
};

int main() {
  int N, Q;
  cin >> N >> Q;
  Graph G(N);
  repeat(i, N - 1) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    G[a].push_back({b});
    G[b].push_back({a});
  }

  const int root = 0;
  LCA lca(G, root);

  while (Q--) {
    int c, d;
    cin >> c >> d;
    --c, --d;
    int dist = lca.length(c, d);
    if (dist % 2)
      cout << "Road" << endl;
    else
      cout << "Town" << endl;
  }
  return 0;
}