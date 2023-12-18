#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

// ref: https://cp-algorithms.com/graph/min_cost_flow.html
struct Edge {
  int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
  d.assign(n, INF);
  d[v0] = 0;
  vector<bool> inqueue(n, false);
  queue<int> q;
  q.push(v0);
  p.assign(n, -1);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    inqueue[u] = false;
    for (int v : adj[u]) {
      if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
        d[v] = d[u] + cost[u][v];
        p[v] = u;
        if (!inqueue[v]) {
          q.push(v);
          inqueue[v] = true;
        }
      }
    }
  }
}

int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
  adj.assign(N, vector<int>());
  cost.assign(N, vector<int>(N, 0));
  capacity.assign(N, vector<int>(N, 0));
  for (Edge e : edges) {
    adj[e.from].push_back(e.to);
    adj[e.to].push_back(e.from);
    cost[e.from][e.to] = e.cost;
    cost[e.to][e.from] = -e.cost;
    capacity[e.from][e.to] = e.capacity;
  }

  int flow = 0;
  int cost = 0;
  vector<int> d, p;
  while (flow < K) {
    shortest_paths(N, s, d, p);
    if (d[t] == INF)
      break;

    // find max flow on that path
    int f = K - flow;
    int cur = t;
    while (cur != s) {
      f = min(f, capacity[p[cur]][cur]);
      cur = p[cur];
    }

    // apply flow
    flow += f;
    cost += f * d[t];
    cur = t;
    while (cur != s) {
      capacity[p[cur]][cur] -= f;
      capacity[cur][p[cur]] += f;
      cur = p[cur];
    }
  }

  if (flow < K)
    return -1;
  else
    return cost;
}

int main() {
  int N, M, F;
  scanf("%d %d %d", &N, &M, &F);
  vector<Edge> edges;
  for (int i = 0; i < M; ++i) {
    int u, v, c, d;
    scanf("%d %d %d %d", &u, &v, &c, &d);
    edges.push_back({u, v, c, d});
  }

  printf("%d\n", min_cost_flow(N, edges, F, 0, N - 1));
}
