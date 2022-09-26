#include <cstdio>
#include <iostream>
#include <limits>
using namespace std;

int n;
long long k;
long long a[100001];
bool check(long long x) {
  long long ate = 0;
  for (int i = 0; i < n; ++i) {
    ate += min(a[i], x);
  }
  return ate <= k;
}

int main() {
  scanf("%d %lld", &n, &k);
  for (int i = 0; i < n; ++i)
    scanf("%lld", &a[i]);

  long long ok = 0, ng = numeric_limits<long long>::max();
  while (ng - ok > 1) {
    long long md = ok + (ng - ok) / 2;
    if (check(md)) {
      ok = md;
    } else {
      ng = md;
    }
  }

  long long ate = 0;
  for (int i = 0; i < n; ++i) {
    ate += min(a[i], ok);
    a[i] -= min(a[i], ok);
  }

  for (int i = 0; i < n && ate < k; ++i) {
    ate += min(a[i], 1LL);
    a[i] -= min(a[i], 1LL);
  }

  for (int i = 0; i < n; ++i) {
    printf("%lld%c", a[i], (i == n - 1) ? '\n' : ' ');
  }
  return 0;
}