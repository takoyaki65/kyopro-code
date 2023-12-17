#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
typedef pair<int, int> PII;

int main() {
  int V, E, r;
  scanf("%d %d %d", &V, &E, &r);
  vector<vector<PII>> G(V);
  for (int i = 0; i < E; ++i) {
    int s, t, d;
    scanf("%d %d %d", &s, &t, &d);
    G[s].push_back(make_pair(t, d));
  }

  vector<int> dist(V, -1);
  // dist[i] = shortest distance from r to i
  // compute dist[..] by Dijkstra's algorithm
  priority_queue<PII, vector<PII>, greater<PII>> que;
  dist[r] = 0;
  que.push(make_pair(0, r));
  while (!que.empty()) {
    auto [d, v] = que.top();
    que.pop();
    if (dist[v] < d)
      continue;
    for (auto [u, c] : G[v]) {
      // edge from v to u with cost c
      if (dist[u] == -1 || dist[u] > dist[v] + c) {
        dist[u] = dist[v] + c;
        que.push(make_pair(dist[u], u));
      }
    }
  }

  for (int i = 0; i < V; ++i) {
    if (dist[i] == -1)
      printf("INF\n");
    else
      printf("%d\n", dist[i]);
  }

  return 0;
}
