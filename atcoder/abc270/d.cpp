#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;
int a[10010];
int dp[10010];
int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < k; ++i)
    scanf("%d", &a[i]);
  dp[0] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < k && a[j] <= i; ++j) {
      dp[i] = max(dp[i], a[j] + (i - a[j]) - dp[i - a[j]]);
    }
    // printf("i: %d\n", i);
  }
  printf("%d\n", dp[n]);
}