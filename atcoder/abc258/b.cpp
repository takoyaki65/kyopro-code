#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
char a[11][11];
const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%s", a[i]);

  long long ans = 0;
  vector<long long> nums;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < 8; ++k) {
        long long val = 0;
        int x = i, y = j;
        for (int l = 0; l < n; ++l) {
          val = (val * 10LL) + (a[x][y] - '0');
          x = (x + dx[k] + n) % n;
          y = (y + dy[k] + n) % n;
        }
        ans = max(ans, val);
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}