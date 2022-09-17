#include <bits/stdc++.h>

using namespace std;

long a[2010];
long long dp[2010][2010];

int main() {
  int m, n;
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (i == j)
        dp[i][j] = dp[i - 1][j - 1] + a[i - 1] * j;
      else if (i > j)
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + a[i - 1] * j);
    }
  }

  cout << dp[n][m] << endl;
  return 0;
}