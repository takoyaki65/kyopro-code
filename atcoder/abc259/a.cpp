#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  int n, m, x, t, d;
  cin >> n >> m >> x >> t >> d;
  if (x <= m) {
    cout << t << endl;
  } else {
    cout << t - d * (x - m) << endl;
  }
  return 0;
}