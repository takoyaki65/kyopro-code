#include <bits/stdc++.h>
using namespace std;

vector<int> G[200010];
bool visited[200010];

void dfs(int v, int& vcnt, int& ecnt) {
  visited[v] = true;
  vcnt += 1;
  ecnt += G[v].size();
  for (int to : G[v]) {
    if (!visited[to])
      dfs(to, vcnt, ecnt);
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  int ans = 1;
  for (int i = 0; i < n; ++i) {
    if (visited[i])
      continue;

    int vcnt = 0, ecnt = 0;
    dfs(i, vcnt, ecnt);
    ecnt /= 2;
    if (vcnt == ecnt) {
      ans = ((long long)ans * 2LL) % 998244353LL;
    } else {
      ans *= 0;
    }
  }

  cout << ans << endl;
  return 0;
}