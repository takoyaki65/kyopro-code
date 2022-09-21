#include <iostream>
using namespace std;

int a[100010];
int y[100010];

int main() {
  int n, m;
  long long t;
  cin >> n >> m >> t;
  for (int i = 0; i < n - 1; ++i)
    cin >> a[i];
  for (int i = 0; i < m; ++i) {
    int loc;
    cin >> loc;
    cin >> y[loc - 1];
  }

  for (int cur = 0; cur < n - 1; ++cur) {
    if (t <= a[cur]) {
      cout << "No" << endl;
      return 0;
    }
    t -= a[cur];
    t += y[cur + 1];
  }
  cout << "Yes" << endl;
  return 0;
}