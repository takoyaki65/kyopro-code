#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  vector<vector<pair<int, int>>> pes(n);
  for (int i = 0; i < n; ++i) {
    int m;
    scanf("%d", &m);
    for (int j = 0; j < m; ++j) {
      int p, e;
      scanf("%d %d", &p, &e);
      pes[i].push_back({p, e});
    }
  }

  map<int, pair<int, int>> lcm;
  for (const auto& pe : pes) {
    for (const auto [p, e] : pe) {
      auto itr = lcm.find(p);
      if (itr == lcm.end()) {
        lcm[p] = {e, 1};
      } else {
        int& emax = itr->second.first;
        int& icount = itr->second.second;
        if (emax < e) {
          emax = e;
          icount = 1;
        } else if (emax == e) {
          icount += 1;
        }
      }
    }
  }

  int c = 0;
  for (const auto& pe : pes) {
    bool flag = false;
    for (const auto [p, e] : pe) {
      auto itr = lcm.find(p);
      assert(itr != lcm.end());
      if (itr->second.first == e && itr->second.second == 1) {
        flag = true;
        break;
      }
    }
    c += (flag == true);
  }

  int ans = min(c + 1, n);
  printf("%d\n", ans);

  return 0;
}