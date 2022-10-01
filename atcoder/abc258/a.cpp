#include <cstdio>
using namespace std;
int main() {
  int m;
  scanf("%d", &m);
  int h = 21;
  while (m >= 60)
    h += 1, m -= 60;
  printf("%2d:%02d\n", h, m);
  return 0;
}