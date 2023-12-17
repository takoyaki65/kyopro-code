#include <algorithm>
#include <cassert>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
typedef pair<int, long long> PII;

const long long INF = (1LL << 40) - 1;

// Compute all pairs shortest path with negative weight edges.
// First, reweight edges so that all edge weights are non-negative by Johnson's
// algorithm. Then, compute all pairs shortest path by Dijkstra's algorithm.
// After that, compute the original shortest path from the reweighted shortest
// path.
// Time complexity: O(V^2 log V + VE)
// reference: https://en.wikipedia.org/wiki/Johnson%27s_algorithm

// original graph
long long G[101][101];

// reweighted graph
long long Gd[101][101];

long long dist[101];

long long dist_Gd[101][101];
long long dist_G[101][101];

int main() {
  int V, E;
  scanf("%d %d", &V, &E);

  // fill the graph matrix G with INF
  // V-th vertex is super source vertex (used by Johnson's algorithm)
  for (int i = 0; i < V + 1; i++) {
    fill(G[i], G[i] + (V + 1), INF);
  }
  for (int i = 0; i < V + 1; i++) {
    G[i][i] = 0;
  }
  // add edges from super source(V-th vertex) to all 0..(V-1)-th vertices with
  // weight 0.
  for (int i = 0; i < V; i++) {
    G[V][i] = 0;
  }

  // read edges
  for (int i = 0; i < E; i++) {
    int s, t, d;
    scanf("%d %d %d", &s, &t, &d);
    G[s][t] = d;
  }

  // Put super source V-th vertex and connect it to all vertices with weight 0.
  // calculate shortest paths from super source(V-th vertex) to all
  // 0,1,...,V-1 vertices.
  // Result is stored in h.
  // Algorithm: Bellman-Ford
  fill(dist, dist + V, INF);
  dist[V] = 0;
  int last_updated_vertex = -1;
  for (int i = 0; i < V + 1; ++i) {
    last_updated_vertex = -1;
    for (int v = 0; v < V + 1; ++v) {
      for (int u = 0; u < V + 1; ++u) {
        if (dist[v] > dist[u] + G[u][v]) {
          dist[v] = dist[u] + G[u][v];
          last_updated_vertex = v;
        }
      }
    }
  }

  // If last_updated_vertex is not -1, there is a negative cycle.
  // In this case, we can't compute shortest path.
  if (last_updated_vertex != -1) {
    printf("NEGATIVE CYCLE\n");
    return 0;
  }

  // reweight edges, and store the reweighted graph in Gd.
  for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
      if (G[i][j] != INF) {
        Gd[i][j] = G[i][j] + dist[i] - dist[j];
      } else {
        Gd[i][j] = INF;
      }
    }
  }

  // compute all pairs (0 ~ V-1-th) shortest path by Dijkstra's algorithm for
  // the reweighted graph Gd.
  for (int s = 0; s < V; ++s) {
    // s: source vertex
    // compute shortest path from s to all vertices.
    // Algorithm: Dijkstra's algorithm
    fill(dist_Gd[s], dist_Gd[s] + V, INF);
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    dist_Gd[s][s] = 0;
    pq.push(make_pair(0, s));
    while (!pq.empty()) {
      auto [d, v] = pq.top();
      pq.pop();
      if (dist_Gd[s][v] < d) {
        continue;
      }
      for (int u = 0; u < V; ++u) {
        if (dist_Gd[s][u] > dist_Gd[s][v] + Gd[v][u]) {
          dist_Gd[s][u] = dist_Gd[s][v] + Gd[v][u];
          pq.push(make_pair(dist_Gd[s][u], u));
        }
      }
    }
  }

  // compute the original shortest path from the reweighted shortest path.
  for (int u = 0; u < V; ++u) {
    for (int v = 0; v < V; ++v) {
      if (dist_Gd[u][v] == INF) {
        dist_G[u][v] = INF;
      } else {
        dist_G[u][v] = dist_Gd[u][v] - dist[u] + dist[v];
      }
    }
  }

  // print the result
  for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V - 1; ++j) {
      if (dist_G[i][j] == INF) {
        printf("INF ");
      } else {
        printf("%lld ", dist_G[i][j]);
      }
    }
    if (dist_G[i][V - 1] == INF) {
      printf("INF\n");
    } else {
      printf("%lld\n", dist_G[i][V - 1]);
    }
  }

  return 0;
}
