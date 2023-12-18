#include <algorithm>
#include <cstdio>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// ref: https://cp-algorithms.com/graph/edmonds_karp.html
const int INF = 1e9;

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

// compute augmenting path and return the amount of flow
int bfs(int s, int t, vector<int>& parent) {
  fill(parent.begin(), parent.end(), -1);
  parent[s] = -2;
  queue<pair<int, int>> q;
  q.push({s, INF});

  while (!q.empty()) {
    int cur = q.front().first;
    int flow = q.front().second;
    q.pop();

    for (int next : adj[cur]) {
      if (parent[next] == -1 && capacity[cur][next] > 0) {
        parent[next] = cur;
        int new_flow = min(flow, capacity[cur][next]);
        if (next == t) {
          return new_flow;
        }
        q.push({next, new_flow});
      }
    }
  }
  return 0;
}

int main() {
  int m;
  scanf("%d%d", &n, &m);
  capacity.resize(n, vector<int>(n, 0));
  adj.resize(n, vector<int>());
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    capacity[u][v] = c;
    // capacity[v][u] = 0;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int max_flow = 0;
  vector<int> parent(n);
  int new_flow;
  int s = 0, t = n - 1;

  while ((new_flow = bfs(s, t, parent)) > 0) {
    max_flow += new_flow;
    int cur = t;
    while (cur != s) {
      int prev = parent[cur];
      capacity[prev][cur] -= new_flow;
      capacity[cur][prev] += new_flow;
      cur = prev;
    }
  }

  printf("%d\n", max_flow);

  return 0;
}
