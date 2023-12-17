#include <cstdio>
#include <utility>
#include <vector>

using namespace std;
typedef pair<int, long long> PII;

const long long INF = (1LL << 31) - 1;

int main() {
  int V, E, r;
  scanf("%d %d %d", &V, &E, &r);
  vector<vector<PII>> G(V);
  for (int i = 0; i < E; ++i) {
    int s, t, d;
    scanf("%d %d %d", &s, &t, &d);
    G[s].push_back(make_pair(t, d));
  }

  vector<int> dist(V, INF);
  // dist[i] = shortest distance from r to i
  // compute dist[..] by Bellman-Ford's algorithm
  dist[r] = 0;
  int last_updated_destination = -1;
  for (int i = 0; i < V; ++i) {
    last_updated_destination = -1;
    for (int v = 0; v < V; ++v) {
      if (dist[v] == INF)
        continue;
      for (auto [u, c] : G[v]) {
        // edge from v to u with cost c
        if (dist[u] > dist[v] + c) {
          dist[u] = dist[v] + c;
          last_updated_destination = u;
        }
      }
    }
    // printf("i = %d\n", i);
    // for (int i = 0; i < V; ++i) {
    //   if (dist[i] == INF)
    //     printf("INF ");
    //   else
    //     printf("%d ", dist[i]);
    // }
    // printf("\n");
  }

  // If last_updated_destination is not -1 after V-th iteration,
  // there exists a negative cycle.
  if (last_updated_destination != -1) {
    printf("NEGATIVE CYCLE\n");
    return 0;
  }

  for (int i = 0; i < V; ++i) {
    if (dist[i] == INF)
      printf("INF\n");
    else
      printf("%d\n", dist[i]);
  }
  return 0;
}
