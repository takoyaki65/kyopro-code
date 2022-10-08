#include <algorithm>
#include <cstdio>
using namespace std;
int a[300010];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  sort(a, a + n);
  int p = unique(a, a + n) - a;
  // [0, p) unique
  // [p, n) otherwise
  int sold = n - p;
  int ans = 0;
  int l = 0;
  int r = p - 1;
  while (true) {
    if (l <= r && a[l] == ans + 1) {
      l += 1;
      ans += 1;
    } else {
      if (sold >= 2) {
        sold -= 2;
        ans += 1;
      } else if (l <= r) {
        r -= 1;
        sold += 1;
      } else {
        break;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}