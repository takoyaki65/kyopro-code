#include <iostream>
using namespace std;

bool g[101][101];

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u][v] = g[v][u] = true;
  }

  int ans = 0;
  for (int a = 0; a < n - 2; ++a) {
    for (int b = a + 1; b < n - 1; ++b) {
      for (int c = b + 1; c < n; ++c) {
        if (g[a][b] && g[b][c] && g[c][a])
          ans += 1;
      }
    }
  }
  cout << ans << endl;
  return 0;
}