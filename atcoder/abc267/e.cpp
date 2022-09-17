#include <cassert>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  vector<vector<int>> graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  vector<long long> cost(n, 0LL);
  for (int u = 0; u < n; ++u) {
    for (int v : graph[u]) {
      cost[u] += a[v];
    }
  }

  auto check = [&](long long x) -> bool {
    vector<long long> ctemp = cost;
    vector<bool> exist(n, true);
    stack<int> vertices;
    int erased = 0;
    for (int u = 0; u < n; ++u)
      if (ctemp[u] <= x)
        vertices.push(u);

    while (!vertices.empty()) {
      int u = vertices.top();
      vertices.pop();
      if (!exist[u])
        continue;
      exist[u] = false;
      for (int v : graph[u]) {
        ctemp[v] -= a[u];
        if (exist[v] && ctemp[v] <= x)
          vertices.push(v);
      }
      erased += 1;
    }

    return erased == n;
  };

  long long ng = -1, ok = 2000000000000000LL;
  while (ok - ng > 1) {
    // cout << "[" << ng << "," << ok << "]" << endl;
    long long mid = ng + (ok - ng) / 2;
    if (check(mid))
      ok = mid;
    else
      ng = mid;
  }

  cout << ok << endl;
  return 0;
}