#include <iostream>
#include <map>
#include <set>
#include <utility>
using namespace std;
#define MOD 998244353

int main() {
  int n, m, a, b, c, d, e, f;
  cin >> n >> m >> a >> b >> c >> d >> e >> f;
  set<pair<long long, long long>> obst;
  for (int i = 0; i < m; ++i) {
    long long x, y;
    cin >> x >> y;
    obst.insert({x, y});
  }
  map<pair<long long, long long>, long long> dp;

  dp[{0, 0}] = 1;
  for (int i = 0; i < n; ++i) {
    map<pair<long long, long long>, long long> new_dp;
    for (auto [xy, p] : dp) {
      auto [x, y] = xy;
      if (!obst.count({x + a, y + b}))
        new_dp[{x + a, y + b}] = (new_dp[{x + a, y + b}] + p) % MOD;
      if (!obst.count({x + c, y + d}))
        new_dp[{x + c, y + d}] = (new_dp[{x + c, y + d}] + p) % MOD;
      if (!obst.count({x + e, y + f}))
        new_dp[{x + e, y + f}] = (new_dp[{x + e, y + f}] + p) % MOD;
    }
    swap(dp, new_dp);
  }

  long long res = 0;
  for (auto [xy, p] : dp) {
    res = (res + p) % MOD;
  }

  cout << res << endl;
  return 0;
}