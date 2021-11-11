#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> xs(n), ys(n);
  for (int i = 0; i < n; ++i)
    cin >> xs[i] >> ys[i];

  set<pair<int, int>> dxys;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int dx = xs[i] - xs[j];
      int dy = ys[i] - ys[j];
      int div = __gcd(abs(dx), abs(dy));
      dx /= div, dy /= div;
      dxys.insert({dx, dy});
      dxys.insert({-dx, -dy});
    }
  }
  cout << dxys.size() << endl;
  return 0;
}