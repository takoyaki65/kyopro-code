#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<vector<int>> graph(n);
  vector<int> in_deg(n, 0);
  for (int i = 0; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    graph[u].push_back(v);
    graph[v].push_back(u);
    in_deg[u] += 1;
    in_deg[v] += 1;
  }

  vector<bool> loop(n, true);
  {
    stack<int> vertices;
    for (int u = 0; u < n; ++u)
      if (in_deg[u] == 1)
        vertices.push(u);

    while (!vertices.empty()) {
      int u = vertices.top();
      vertices.pop();
      if (!loop[u])
        continue;
      loop[u] = false;
      for (int v : graph[u]) {
        if (loop[v]) {
          in_deg[v] -= 1;
          if (in_deg[v] == 1) {
            vertices.push(v);
          }
        }
      }
    }
  }

  vector<int> root(n, -1);
  auto dfs = [&](auto f, int u, int prev, int color) -> void {
    root[u] = color;
    for (int v : graph[u]) {
      if (v != prev && !loop[v]) {
        f(f, v, u, color);
      }
    }
  };
  for (int u = 0; u < n; ++u) {
    if (loop[u]) {
      dfs(dfs, u, -1, u);
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    if (root[x] == root[y])
      cout << "Yes" << endl;
    else
      cout << "No" << endl;
  }
  return 0;
}