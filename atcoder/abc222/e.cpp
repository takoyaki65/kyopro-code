#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

int dfs(int v,
        int goal,
        vector<vector<pair<int, int>>>& g,
        vector<bool>& visited,
        vector<int>& count) {
  if (v == goal) {
    return 1;
  }
  // ret := 0 if there is no path from v to goal, 1 otherwise
  for (auto [id, to] : g[v]) {
    if (visited[to]) {
      continue;
    }
    visited[to] = true;
    if (dfs(to, goal, g, visited, count)) {
      count[id]++;
      return 1;
    }
  }
  return 0;
}

int main() {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  vector<int> a(m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &a[i]);
    a[i]--;
  }

  // g[i][j] = (id, to)
  // id-th edge from i to to
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    g[u].emplace_back(i, v);
    g[v].emplace_back(i, u);
  }

  // We traverse the graph from 0-th node to 1-th node by shortest path,
  // then traverse from 1-th node to 2-th node by shortest path, and so on.
  // After that, for each edge, we count how many times it is passed.
  vector<int> count(n - 1, 0);

  vector<bool> visited(n, false);
  for (int i = 0; i < m - 1; ++i) {
    // traverse from a[i]-th node to a[i+1]-th node
    visited.assign(n, false);
    visited[a[i]] = true;
    dfs(a[i], a[i + 1], g, visited, count);
  }

  // calculate all possible selections from (count[0], ..., count[n-2])
  // such that sum of them is (s + k)/2
  // (s = sum of count[0], ..., count[n-2])
  int s = 0;
  for (int i = 0; i < n - 1; i++) {
    s += count[i];
  }
  if ((s + k) % 2 != 0 || s + k < 0) {
    printf("0\n");
    return 0;
  }
  //printf("s = %d\n", s);
  const int MOD = 998244353;
  // dp[j] := number of ways to select some elements from count[0], ...,
  // count[n-2] so that sum of them is j
  vector<int> dp((s + k) / 2 + 1, 0);
  dp[0] = 1;
  for (int i = 0; i < n - 1; i++) {
    for (int j = dp.size() - 1; j >= count[i]; j--) {
      dp[j] += dp[j - count[i]];
      dp[j] %= MOD;
    }
  }
  printf("%d\n", dp[(s + k) / 2]);
}
