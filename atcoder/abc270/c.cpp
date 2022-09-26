#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int n, x, y;
vector<int> g[200000];
int par[200000];
void dfs(int u, int k, int goal) {
  par[u] = k;
  if (u == goal)
    return;
  for (const auto v : g[u]) {
    if (v != k)
      dfs(v, u, goal);
  }
}
int main() {
  scanf("%d %d %d", &n, &x, &y);
  --x, --y;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  memset(par, -1, sizeof(par));
  dfs(y, -1, x);

  int v = x;
  while (v != -1) {
    printf("%d", v + 1);
    v = par[v];
    printf("%c", (v != -1) ? ' ' : '\n');
  }

  return 0;
}
