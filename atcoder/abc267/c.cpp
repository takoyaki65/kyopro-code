#include <iostream>
using namespace std;

long long a[200010];
long long sum[200010];

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  // sum[i] := sum of a[i-m, i)
  for (int i = 0; i < m; ++i)
    sum[m] += a[i];

  for (int i = m + 1; i <= n; ++i)
    sum[i] = sum[i - 1] + a[i - 1] - a[i - 1 - m];

  long long ans;
  long long res = 0;

  for (int i = 0; i < m; ++i) {
    res += a[i] * (i + 1);
  }

  ans = res;
  for (int i = m + 1; i <= n; ++i) {
    res = res + a[i - 1] * m - sum[i - 1];
    if (ans < res)
      ans = res;
  }

  cout << ans << endl;

  return 0;
}