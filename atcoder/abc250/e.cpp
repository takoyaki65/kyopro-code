#include <algorithm>
#include <cassert>
#include <cstdio>
#include <set>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  std::vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
  }

  // preprocess
  std::vector<int> a_prefix_set_size(n);
  std::vector<int> b_prefix_set_size(n);
  std::vector<int> a_inserted;
  std::vector<int> b_inserted;
  {
    std::set<int> s;
    for (int i = 0; i < n; ++i) {
      auto it = s.find(a[i]);
      if (it == s.end()) {
        a_inserted.push_back(a[i]);
      }
      s.insert(a[i]);
      a_prefix_set_size[i] = s.size();
    }
    s.clear();
    for (int i = 0; i < n; ++i) {
      auto it = s.find(b[i]);
      if (it == s.end()) {
        b_inserted.push_back(b[i]);
      }
      s.insert(b[i]);
      b_prefix_set_size[i] = s.size();
    }
  }

  const int max_k = std::max(a_inserted.size(), b_inserted.size());
  const int min_k = std::min(a_inserted.size(), b_inserted.size());
  std::vector<bool> k2query(max_k, false);
  {
    std::set<int> s;
    for (int k = 0; k < min_k; ++k) {
      {
        auto it = s.find(a_inserted[k]);
        if (it == s.end()) {
          s.insert(a_inserted[k]);
        } else {
          s.erase(it);
        }
      }
      {
        auto it = s.find(b_inserted[k]);
        if (it == s.end()) {
          s.insert(b_inserted[k]);
        } else {
          s.erase(it);
        }
      }
      if (s.empty()) {
        k2query[k] = true;
      }
    }
  }

  int q;
  scanf("%d", &q);
  while(q--) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x, --y;
    if (a_prefix_set_size[x] != b_prefix_set_size[y]) {
      printf("No\n");
      continue;
    }
    int k = a_prefix_set_size[x] - 1;
    assert(k < min_k);
    if (k2query[k]) {
      printf("Yes\n");
    } else {
      printf("No\n");
    }
  }

  return 0;
}