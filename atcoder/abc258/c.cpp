#include <cstdio>
using namespace std;
char s[500010];
int main() {
  int n, q;
  scanf("%d %d", &n, &q);
  scanf("%s", s);
  int begin = 0;
  while (q--) {
    int t, x;
    scanf("%d %d", &t, &x);
    if (t == 1) {
      begin = (begin - x + n) % n;
    } else {
      x -= 1;
      printf("%c\n", s[(begin + x) % n]);
    }
  }
}