#include <iostream>
#include <set>
using namespace std;
int a[200010];
int main() {
  int n;
  long long p, q, r;
  cin >> n >> p >> q >> r;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  set<long long> sums;
  {
    long long s = 0;
    sums.insert(s);
    for (int i = 0; i < n; ++i) {
      s += a[i];
      sums.insert(s);
    }
  }

  long long sx = 0;
  long long sy = sx + p;
  long long sz = sy + q;
  long long sw = sz + r;
  for (int x = 0; x < n - 2; ++x) {
    if (sums.count(sy) && sums.count(sz) && sums.count(sw)) {
      cout << "Yes" << endl;
      return 0;
    }

    sx += a[x];
    sy = sx + p;
    sz = sy + q;
    sw = sz + r;
  }
  cout << "No" << endl;
  return 0;
}