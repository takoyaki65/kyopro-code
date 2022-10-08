#include <cstdio>
#include <vector>
using namespace std;
int main() {
  int n, q;
  scanf("%d %d", &n, &q);
  vector<vector<int>> tbl(n);
  for (int i = 0; i < n; ++i) {
    int len;
    scanf("%d", &len);
    for (int j = 0; j < len; ++j) {
      int v;
      scanf("%d", &v);
      tbl[i].push_back(v);
    }
  }
  for (int i = 0; i < q; ++i) {
    int s, t;
    scanf("%d %d", &s, &t);
    --s, --t;
    printf("%d\n", tbl[s][t]);
  }
}