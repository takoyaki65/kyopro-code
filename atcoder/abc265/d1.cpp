#include <iostream>
using namespace std;

int a[200010];
long long s[200010];
int main() {
  int n;
  long long p, q, r;
  cin >> n >> p >> q >> r;
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + a[i - 1];

  int x = 0, y = 0, z = 0, w = 0;
  long long sx, sy, sz, sw;
  for (; x < n - 2; ++x) {
    sx = s[x];
    sy = sx + p;
    sz = sy + q;
    sw = sz + r;
    while (y + 1 <= n && s[y + 1] <= sy)
      ++y;
    while (z + 1 <= n && s[z + 1] <= sz)
      ++z;
    while (w + 1 <= n && s[w + 1] <= sw)
      ++w;

    if (sy == s[y] && sz == s[z] && sw == s[w]) {
      cout << "Yes" << endl;
      return 0;
    }
  }
  cout << "No" << endl;
  return 0;
}