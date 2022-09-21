#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

int x[100010];
int a[100010];
long long dp1[5], dp2[5];

int main() {
  int n;
  cin >> n;
  memset(x, -1, sizeof(x));
  memset(a, -1, sizeof(a));
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    cin >> x[t] >> a[t];
  }

  long long *prev = dp1, *next = dp2;
  prev[0] = 0, prev[1] = -1, prev[2] = -1, prev[3] = -1, prev[4] = -1;

  for (int i = 1; i <= 100000; ++i) {
    for (int pos = 0; pos < 5; ++pos)
      next[pos] = -1;
    for (int pos = 0; pos < 5; ++pos) {
      for (int k = -1; k <= 1; ++k) {
        int prev_pos = pos + k;
        if (prev_pos >= 0 && prev_pos < 5 && prev[prev_pos] >= 0) {
          next[pos] = max(next[pos], prev[prev_pos] + (pos == x[i] ? a[i] : 0));
        }
      }
    }
    swap(prev, next);
  }

  cout << *max_element(prev, prev + 5) << endl;
  return 0;
}