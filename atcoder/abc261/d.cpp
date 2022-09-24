#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
long long dp1[5001], dp2[5001];
long long x[5001], bonus[5001];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> x[i];
  for (int i = 0; i < m; ++i) {
    int c, y;
    cin >> c >> y;
    bonus[c] = y;
  }

  long long *prev = dp1, *next = dp2;
  memset(prev, -1, sizeof(dp1));
  prev[0] = 0;
  for (int i = 0; i < n; ++i) {
    memset(next, -1, sizeof(dp1));
    next[0] = prev[0];
    for (int j = 1; j <= i + 1; ++j) {
      // head (j-1 -> j)
      if (prev[j - 1] != -1)
        next[j] = max(next[j], prev[j - 1] + x[i] + bonus[j]);

      // tail (j -> 0)
      if (prev[j] != -1)
        next[0] = max(next[0], prev[j] + bonus[0]);
    }
    swap(prev, next);
  }

  cout << *max_element(prev, prev + (n + 1)) << endl;
  return 0;
}
