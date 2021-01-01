#include <bits/stdc++.h>
using namespace std;

int main() {
  int n{0};
  cin >> n;
  n *= 2;
  int l[n] = {0};
  for (int i = 0; i < n; ++i) cin >> l[i];
  sort(l, l + n);
  int ans = 0;
  for (int i = 0; i < n; i += 2) {
    ans += min(l[i], l[i + 1]);
  }
  cout << ans << endl;
  return 0;
}