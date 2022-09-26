#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
  int x, y, z;
  scanf("%d %d %d", &x, &y, &z);
  if (x < 0)
    x = -x, y = -y, z = -z;

  // 0 < x
  if (0 < y && y < x) {
    if (y < z) {
      printf("-1\n");
    } else {
      printf("%d\n", abs(z) + (x - z));
    }
  } else {
    printf("%d\n", x);
  }

  return 0;
}