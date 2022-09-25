#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
int ans[200000];
int under[200000];
int pile[200000];
int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  set<int> table;

  memset(under, -1, sizeof(under));
  memset(ans, -1, sizeof(ans));

  for (int i = 1; i <= n; ++i) {
    int p;
    scanf("%d", &p);
    --p;
    auto itr = table.upper_bound(p);
    // itr = upper_bound(table.begin(), table.end(), p);
    if (itr == table.end()) {
      pile[p] = 1;
    } else {
      int q = *itr;
      under[p] = q;
      pile[p] = pile[q] + 1;
      table.erase(itr);
    }
    table.insert(p);
    if (pile[p] == k) {
      while (p != -1) {
        ans[p] = i;
        table.erase(p);
        p = under[p];
      }
    }
  }

  for (int i = 0; i < n; ++i)
    printf("%d\n", ans[i]);
  return 0;
}