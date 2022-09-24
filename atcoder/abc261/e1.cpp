#include <cstdio>
#include <iostream>
using namespace std;
int main() {
  int n, c;
  scanf("%d %d", &n, &c);
  const int m = (1 << 30) - 1;
  int s0 = 0, s1 = m;
  int x = c;
  for (int idx = 0; idx < n; ++idx) {
    int t, a;
    scanf("%d %d", &t, &a);
    if (t == 1)
      s0 &= a, s1 &= a;
    else if (t == 2)
      s0 |= a, s1 |= a;
    else if (t == 3)
      s0 ^= a, s1 ^= a;
    x = ((x ^ m) & s0) | (x & s1);
    printf("%d\n", x);
  }
  return 0;
}