#include <iostream>
using namespace std;
int a[500010];
int idacum[500010];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    --a[i];
  }
  for (int i = 0; i < n; ++i) {
    idacum[i + 1] = idacum[i] + (a[i] == i);
  }

  long long ans = 0;
  for (int j = n - 1; j >= 1; --j) {
    if (a[j] == j) {
      ans += idacum[j];
    } else {
      int i = a[j];
      if (i < j && a[i] == j)
        ans += 1;
    }
  }
  cout << ans << endl;
  return 0;
}
