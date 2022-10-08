#include <iostream>
#include <vector>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  vector<bool> set(n + 2);
  for (int i = 0; i < n; ++i) {
    int a;
    scanf("%d", &a);
    set[min(n + 1, a)] = true;
  }
  for (int read = 1; n >= 0; ++read) {
    n -= set[read] ? 1 : 2;
    if (n < 0)
      printf("%d\n", read - 1);
  }
}