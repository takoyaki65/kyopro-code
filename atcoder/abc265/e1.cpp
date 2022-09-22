#include <cstring>
#include <iostream>
#include <set>
#include <utility>
using namespace std;
int dxs[3], dys[3];
#define MOD 998244353

long long dp1[310][310], dp2[310][310];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < 3; ++i)
    cin >> dxs[i] >> dys[i];
  set<pair<int, int>> obst;
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    obst.insert({x, y});
  }
  auto *prev = dp1, *next = dp2;
  prev[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (long long a = 0; a <= i; ++a) {
      for (long long b = 0; b <= i - a; ++b) {
        long long x = a * dxs[0] + b * dxs[1] + (i - a - b) * dxs[2];
        long long y = a * dys[0] + b * dys[1] + (i - a - b) * dys[2];
        for (int k = 0; k < 3; ++k) {
          long long nx = x + dxs[k], ny = y + dys[k];
          if (obst.count({nx, ny}) == 0) {
            next[a + (k == 0)][b + (k == 1)] =
                (next[a + (k == 0)][b + (k == 1)] + prev[a][b]) % MOD;
          }
        }
      }
    }
    swap(prev, next);
    memset(next, 0, sizeof(dp1));
  }

  long long ans = 0;
  for (int a = 0; a <= n; ++a) {
    for (int b = 0; b <= n; ++b) {
      ans = (ans + prev[a][b]) % MOD;
    }
  }
  cout << ans << endl;
  return 0;
}