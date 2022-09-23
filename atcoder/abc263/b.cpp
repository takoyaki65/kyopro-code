#include <iostream>
using namespace std;
int p[51];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    cin >> p[i];
    p[i] -= 1;
  }
  int ans = 0;
  int x = n - 1;
  while (x > 0) {
    x = p[x];
    ans += 1;
  }
  cout << ans << endl;
  return 0;
}
