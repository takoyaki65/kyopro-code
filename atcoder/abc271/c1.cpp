#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  vector<bool> vol(n + 2, false);
  vector<int> a(n);

  int sold = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    if (a[i] >= vol.size())
      sold++;
    else if (vol[a[i]])
      sold++;
    else
      vol[a[i]] = true;
  }

  int l = 1;
  int r = n + 1;
  while (true) {
    while (vol[l])
      l++;
    while (r != 0 && !vol[r])
      r--;
    if (sold >= 2) {
      sold -= 2;
      vol[l] = true;
    } else {
      if (l >= r)
        break;
      vol[r] = false;
      sold++;
    }
  }
  printf("%d\n", l - 1);
  return 0;
}