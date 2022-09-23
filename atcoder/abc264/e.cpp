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
  vector<int> u(e), v(e);
  for (int i = 0; i < e; ++i) {
    cin >> u[i] >> v[i];
    --u[i], --v[i];
  }

  int q;
  cin >> q;
  vector<int> x(q);
  for (int i = 0; i < q; ++i) {
    cin >> x[i];
    --x[i];
  }

  vector<bool> available(e, true);
  for (int i = 0; i < q; ++i)
    available[x[i]] = false;

  UnionFind uf(n + m);
  for (int i = n; i < n + m - 1; ++i)
    uf.unite(i, i + 1);
  for (int i = 0; i < e; ++i) {
    if (available[i]) {
      uf.unite(u[i], v[i]);
    }
  }

  int ens = 0;
  for (int i = 0; i < n; ++i) {
    if (uf.same(i, n))
      ens += 1;
  }
  vector<int> ans(q);
  for (int i = q - 1; i >= 0; --i) {
    ans[i] = ens;

    bool u_is_en = uf.same(u[x[i]], n);
    bool v_is_en = uf.same(v[x[i]], n);

    if (u_is_en && !v_is_en) {
      ens += uf.size(v[x[i]]);
    } else if (!u_is_en && v_is_en) {
      ens += uf.size(u[x[i]]);
    }

    uf.unite(u[x[i]], v[x[i]]);
  }

  for (int i = 0; i < q; ++i)
    cout << ans[i] << endl;

  return 0;
}