// reference: https://codeforces.com/blog/entry/95823
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

template <typename Cap, typename Cost>
class MinCostMaxFlow {
 public:
  MinCostMaxFlow(int n_)
      : n(n_), g(n_), potential(n_), f(n_), vis(n_), par(n_) {}
  void add_edge(int u, int v, Cap cap, Cost cost) {
    int k = e.size();
    e.push_back({v, cap, 0, cost});
    e.push_back({u, cap, cap, -cost});
    g[u].push_back(k);
    // k ^ 1 = k xor 1 = k + 1 because k is even(0, 2, 4, ...)
    g[v].push_back(k ^ 1 /* = k + 1*/);
  }
  std::pair<Cap, Cost> solve(int s, int t) {
    Cap flow = 0;
    Cost cost = 0;
    while (true) {
      // find shortest path w.r.t cost from s to t in the residual graph
      std::fill(dist.begin(), dist.end(), std::numeric_limits<Cost>::max());
      std::fill(vis.begin(), vis.end(), false);
      dist[s] = 0;
      f[s] = std::numeric_limits<Cap>::max();
      std::priority_queue<std::pair<Cost, int>,
                          std::vector<std::pair<Cost, int>>, std::greater<>>
          Q;
      Q.push({0, s});
      while (!Q.empty()) {
        Cost d, int x;
        std::tie(d, x) = Q.top();
        Q.pop();
        if (vis[x])
          continue;
        vis[x] = true;
        for (int i : g[x]) {
          // d2 = d(s ~> x) + cost(x -> e[i].v)
          // cost(x -> e[i].v) is offset by potential[x] - potential[e[i].v]
          // to make cost(x -> e[i].v) non-negative.
          Cost d2 = d + e[i].cost + potential[x] - potential[e[i].v];
          if (!vis[e[i].v] && e[i].flow < e[i].cap && d2 < dist[e[i].v]) {
            dist[e[i].v] = d2;
            f[e[i].v] = min(f[x], e[i].cap - e[i].flow);
            par[e[i].v] = i;
            Q.push({d2, e[i].v});
          }
        }
      }

      if (!vis[t])
        break;
      // fix distance from s to every vertex in the residual graph
      // by adding potential
      for (int i = 0; i < n; ++i) {
        dist[i] += potential[i] - potential[s];
      }
      cost += dist[t] * f[t];
      flow += f[t];
      int x = t;
      while (x != s) {
        e[par[x]].flow += f[t];
        e[par[x] ^ 1].flow -= f[t];
        x = e[par[x] ^ 1].v;
      }
      // update potential
      dist.swap(potential);
    }
    return {flow, cost};
  }

 private:
  struct edge {
    int v;  // edge directed to v
    Cap cap, flow;
    Cost cost;
  };
  // n: number of vertices
  int n;
  // e := list of edges
  // e[0], e[2], e[4], ...: normal edges with positive cost
  // e[1], e[3], e[5], ...: reverse edges with negative cost
  // To get the reverse edge of e[i], use e[i ^ 1].
  std::vector<edge> e;
  // g[i] := set of indices of edges directed from i.
  // g[i][j] := index of j-th edge directed from i (to e[g[i][j]].v) .
  std::vector<vector<int>> g;
  // dist, potential, f, vis, par: intermediate results
  std::vector<Cost> dist, potential;
  std::vector<Cap> f;
  std::vector<bool> vis;
  std::vector<int> par;
};
