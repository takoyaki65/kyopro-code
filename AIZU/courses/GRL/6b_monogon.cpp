// reference: https://codeforces.com/blog/entry/95823
#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

/**
 * @note O(F * E * log(V)) time complexity
 *       O(V + E) space complexity
 * @param Cap: type of capacity
 * @param Cost: type of cost
 *
 * TODO: time complexity can be improved to O(F(E + V * log(V))) by using
 *       Fibonacci heap insted of binary heap(std::priority_queue).
 */
template <typename Cap, typename Cost>
class MinCostMaxFlow {
 public:
  MinCostMaxFlow(int n_)
      : n(n_), g(n_), dist(n_), potential(n_), f(n_), vis(n_), par(n_) {}
  void add_edge(int u, int v, Cap cap, Cost cost) {
    int k = e.size();
    // assert(k % 2 == 0);
    e.push_back({v, cap, 0, cost});
    e.push_back({u, cap, cap, -cost});
    g[u].push_back(k);
    // k ^ 1 = k xor 1 = k + 1 because k is even(0, 2, 4, ...)
    g[v].push_back(k ^ 1 /* = k + 1*/);
  }

  std::pair<Cap, Cost> solve(int s,
                             int t,
                             Cap flow_limit = std::numeric_limits<Cap>::max(),
                             bool have_negative_cost_edges = false) {
    // assert(0 <= s && s < n);
    // assert(0 <= t && t < n);
    // assert(s != t);
    Cap flow = 0;
    Cost cost = 0;

    if (have_negative_cost_edges) {
      if (!calculate_initial_potential(s)) {
        return {0, 0};
      }
    }

    while (true) {
      // find shortest path w.r.t cost from s to t in the residual graph
      std::fill(dist.begin(), dist.end(), std::numeric_limits<Cost>::max());
      std::fill(vis.begin(), vis.end(), false);
      dist[s] = 0;
      f[s] = flow_limit - flow;
      std::priority_queue<std::pair<Cost, int>,
                          std::vector<std::pair<Cost, int>>, std::greater<>>
          Q;
      Q.push({0, s});
      while (!Q.empty()) {
        Cost d;
        int x;
        std::tie(d, x) = Q.top();
        Q.pop();
        // assert(0 <= x && x < n);
        // assert(d >= 0);
        // assert(0 <= x && x <= vis.size());
        if (vis[x])
          continue;
        vis[x] = true;
        for (int i : g[x]) {
          // assert(0 <= i && i < e.size());
          // assert(0 <= e[i].v && e[i].v < n);
          /*
           * d2 = d(s ~> x) + cost(x -> e[i].v)
           * cost(x -> e[i].v) is offset by potential[x] - potential[e[i].v]
           * to make cost(x -> e[i].v) non-negative.
           */
          Cost d2 = d + e[i].cost + potential[x] - potential[e[i].v];
          if (!vis[e[i].v] && e[i].flow < e[i].cap && d2 < dist[e[i].v]) {
            /*
             * if e[i].flow < e[i].cap, then e[i] is in the residual graph
             * and ofseted cost is positive.
             */
            // assert(e[i].cost + potential[x] - potential[e[i].v] >= 0);
            dist[e[i].v] = d2;
            f[e[i].v] = std::min(f[x], e[i].cap - e[i].flow);
            par[e[i].v] = i;
            Q.push({d2, e[i].v});
          }
        }
      }

      // assert(0 <= t && t < n);
      /*
       * if t is not reachable from s in the residual graph, or
       * if f[t] == 0, then we cannot send flow from s to t anymore.
       */
      if (!vis[t] || f[t] == 0)
        break;
      // assert(f[t] != 0);
      // assert(0 < f[t] && f[t] <= flow_limit - flow);
      /*
       * fix distance from s to every vertex in the residual graph
       * by adding potential
       */
      for (int i = 0; i < n; ++i) {
        dist[i] += potential[i] - potential[s];
      }
      cost += dist[t] * f[t];
      flow += f[t];
      int x = t;
      while (x != s) {
        // assert(0 <= x && x < n);
        // assert(0 <= par[x] && par[x] < e.size());
        // assert(0 <= (par[x] ^ 1) && (par[x] ^ 1) < e.size());
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
  std::vector<std::vector<int>> g;
  // dist, potential, f, vis, par: intermediate results
  std::vector<Cost> dist, potential;
  std::vector<Cap> f;
  std::vector<bool> vis;
  std::vector<int> par;

  bool calculate_initial_potential(int s) {
    // If there are some negative cost edges, then we must calculate
    // initial potential by Bellman-Ford algorithm.
    // SPFA algorithm is applied here.
    // ref:
    // https://cp-algorithms.com/graph/bellman_ford.html#shortest-path-faster-algorithm-spfa
    std::fill(potential.begin(), potential.end(),
              std::numeric_limits<Cost>::max());
    std::vector<int> cnt(n, 0);
    std::vector<bool> in_queue(n, false);
    std::queue<int> Q;

    potential[s] = 0;
    Q.push(s);
    in_queue[s] = true;
    while (!Q.empty()) {
      int x = Q.front();
      Q.pop();
      in_queue[x] = false;

      for (int i : g[x]) {
        /**
         * d := dist(s ~> x) + cost(x -> e[i].v)
         */
        int to = e[i].v;
        Cost d = potential[x] + e[i].cost;
        if (e[i].flow < e[i].cap && d < potential[to]) {
          potential[to] = d;
          if (!in_queue[to]) {
            Q.push(to);
            in_queue[to] = true;
            cnt[to]++;
            if (cnt[to] > n)
              //  std::cout << "negative cycle detected" << std::endl;
              return false;
          }
        }
      }
    }
    return true;
  }
};

#include <cstdio>

int main() {
  int n, m, f;
  scanf("%d %d %d", &n, &m, &f);
  MinCostMaxFlow<int, int> mcmf(n);
  for (int i = 0; i < m; ++i) {
    int u, v, c, d;
    scanf("%d %d %d %d", &u, &v, &c, &d);
    mcmf.add_edge(u, v, c, d);
  }
  // std::cout << "initialize done" << std::endl;

  int flow, cost;
  int s = 0, t = n - 1;
  try {
    std::tie(flow, cost) = mcmf.solve(s, t, f);
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  if (flow == f) {
    printf("%d\n", cost);
  } else {
    printf("-1\n");
  }
  return 0;
}
