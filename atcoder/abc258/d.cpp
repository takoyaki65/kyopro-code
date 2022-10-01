#include <algorithm>
#include <cstdio>
#include <limits>
using namespace std;
int main() {
  int n;
  long long x;
  scanf("%d %lld", &n, &x);
  long long ans = numeric_limits<long long>::max();
  long long acum = 0LL, b_min = numeric_limits<long long>::max();
  for (int i = 1; i <= n; ++i) {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    acum += (a + b);
    b_min = min(b_min, b);
    if (i <= x) {
      ans = min(ans, acum + b_min * (x - i));
    }
  }
  printf("%lld\n", ans);
  return 0;
}