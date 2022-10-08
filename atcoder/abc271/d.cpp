#include <cstdio>
#include <set>
#include <vector>
using namespace std;
int a[101], b[101];
bool dp[101][10001];
bool card[101];
int main() {
  int n, s;
  scanf("%d %d", &n, &s);
  for (int i = 0; i < n; ++i)
    scanf("%d %d", &a[i], &b[i]);

  dp[0][0] = true;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= s; ++j) {
      if (dp[i][j]) {
        if (j + a[i] <= s)
          dp[i + 1][j + a[i]] = true;
        if (j + b[i] <= s)
          dp[i + 1][j + b[i]] = true;
      }
    }
  }

  if (!dp[n][s]) {
    printf("No\n");
    return 0;
  }

  int j = s;
  for (int i = n; i > 0; --i) {
    if (j - a[i - 1] >= 0 && dp[i - 1][j - a[i - 1]]) {
      card[i] = true;
      j -= a[i - 1];
    } else if (j - b[i - 1] >= 0 && dp[i - 1][j - b[i - 1]]) {
      card[i] = false;
      j -= b[i - 1];
    } else {
      printf("error\n");
      return 0;
    }
  }
  printf("Yes\n");
  for (int i = 1; i <= n; ++i) {
    printf("%c", card[i] ? 'H' : 'T');
  }
  printf("\n");
  return 0;
}