#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
long long a[100001];
long long v[100001];
int main() {
  int n;
  long long k;
  scanf("%d %lld", &n, &k);
  for (int i = 0; i < n; ++i)
    scanf("%lld", &a[i]);

  int vsize = 0;
  for (int i = 0; i < n; ++i)
    if (a[i] > 0)
      v[vsize++] = a[i];

  std::sort(v, v + vsize, std::greater<long long>());
  long long ate = 0;
  long long loop = 0;
  for (int i = vsize - 1; i >= 0; --i) {
    if ((v[i] - loop) * (i + 1) <= k - ate) {
      ate += (v[i] - loop) * (i + 1);
      loop = v[i];
    } else {
      loop += (k - ate) / (i + 1);
      ate += (k - ate) / (i + 1) * (i + 1);
    }
    if (k - ate < i + 1)
      break;
  }

  for (int i = 0; i < n; ++i) {
    // loop
    a[i] -= std::min(a[i], loop);
    // other
    if (a[i] > 0 && ate < k)
      a[i] -= 1, ate += 1;
  }

  for (int i = 0; i < n; ++i) {
    printf("%lld%c", a[i], (i == n - 1 ? '\n' : ' '));
  }

  return 0;
}