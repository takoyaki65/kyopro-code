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
  int n, q;
  cin >> n >> q;
  UnionFind uf(n + 1);
  while (q--) {
    int l, r;
    cin >> l >> r;
    uf.unite(l - 1, r);
  }
  if (uf.same(0, n))
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
  return 0;
}