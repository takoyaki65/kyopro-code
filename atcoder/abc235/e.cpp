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

struct edge {
  int u, v, cost, queryID;
};

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<edge> edgeList;
  edgeList.reserve(m + q);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    edgeList.push_back({a, b, c, -1});
  }
  for (int i = 0; i < q; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    edgeList.push_back({u, v, w, i});
  }
  sort(edgeList.begin(), edgeList.end(),
       [](const edge& l, const edge& r) { return l.cost < r.cost; });
  UnionFind uf(n);
  vector<bool> answer(q);
  for (const auto& [u, v, cost, queryID] : edgeList) {
    if (queryID != -1) {
      answer[queryID] = !uf.same(u, v);
    } else {
      if (!uf.same(u, v))
        uf.unite(u, v);
    }
  }
  for (int i = 0; i < q; ++i) {
    cout << (answer[i] ? "Yes" : "No") << endl;
  }
  return 0;
}