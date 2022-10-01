#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  int n, q, x;
  // cin >> n >> q >> x;
  scanf("%d %d %d", &n, &q, &x);
  vector<int> w(2 * n);
  for (int i = 0; i < n; ++i) {
    // cin >> w[i];
    scanf("%d", &w[i]);
    w[i + n] = w[i];
  }
  const ll all = accumulate(begin(w), begin(w) + n, 0ll);
  vector<int> count(n, (x / all) * n);
  x %= all;
  for (int i = 0, j = 0, s = 0; i < n; ++i) {
    if (j < i) {
      j = i;
      s = 0;
    }
    while (s < x) {
      s += w[j];
      j += 1;
    }
    count[i] += j - i;
    s -= w[i];
  }
  vector<int> order(n, -1), path;
  int loop = -1;
  for (int u = 0, k = 0;; ++k) {
    if (order[u] != -1) {
      loop = k - order[u];
      break;
    }
    order[u] = k;
    path.push_back(u);
    u = (u + count[u]) % n;
  }
  const int non_loop = (int)path.size() - loop;
  while (q--) {
    ll k;
    // cin >> k;
    scanf("%lld", &k);
    k -= 1;
    if (k < non_loop) {
      cout << count[path[k]] << '\n';
    } else {
      k = (k - non_loop) % loop;
      cout << count[path[non_loop + k]] << '\n';
    }
  }
}