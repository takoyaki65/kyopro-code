#include <iostream>
#include <limits>
using namespace std;
int a[200010];
long long f[200010], g[200010];
int main() {
  int n;
  long long l, r;
  cin >> n >> l >> r;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  f[0] = 0;
  for (int i = 1; i <= n; ++i) {
    f[i] = min(f[i - 1] + a[i - 1], l * i);
  }

  g[0] = 0;
  for (int i = 1; i <= n; ++i) {
    g[i] = min(g[i - 1] + a[n - i], r * i);
  }

  long long ans = numeric_limits<long long>::max();
  for (int i = 0; i <= n; ++i)
    ans = min(ans, f[i] + g[n - i]);
  cout << ans << endl;
  return 0;
}