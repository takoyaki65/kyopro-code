#include <bits/stdc++.h>
using namespace std;

// https://ei1333.github.io/luzhiled/snippets/structure/union-find.html
struct UnionFind {
  vector<int> data;

  UnionFind(int sz) { data.assign(sz, -1); }

  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
      return (false);
    if (data[x] > data[y])
      swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return (true);
  }

  int find(int k) {
    if (data[k] < 0)
      return (k);
    return (data[k] = find(data[k]));
  }

  int size(int k) { return (-data[find(k)]); }

  bool same(int x, int y) { return find(x) == find(y); }
};

int main() {
  int n, m, e;
  cin >> n >> m >> e;
  vector<pair<int, int>> uv(e);
  for (int i = 0; i < e; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    if (u >= n)
      u = n;
    if (v >= n)
      v = n;
    uv[i] = {u, v};
  }
  int q;
  cin >> q;
  vector<int> query(q);
  vector<bool> available(e, true);
  for (int i = 0; i < q; ++i) {
    cin >> query[i];
    --query[i];
    available[query[i]] = false;
  }

  UnionFind uf(n + 1);
  for (int i = 0; i < e; ++i) {
    if (available[i])
      uf.unite(uv[i].first, uv[i].second);
  }

  vector<int> ans(q);
  for (int i = q - 1; i >= 0; --i) {
    ans[i] = uf.size(n) - 1;

    auto [u, v] = uv[query[i]];
    uf.unite(u, v);
  }

  for (const auto& a : ans)
    cout << a << endl;

  return 0;
}