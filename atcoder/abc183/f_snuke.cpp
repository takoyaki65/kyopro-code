#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T& x) {
  return x.size();
}

template <class T>
inline bool setmax(T& a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T& a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}

template <typename T, typename X>
auto vectors(T a, X x) {
  return vector<T>(x, a);
}

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
  auto cont = vectors(a, y, zs...);
  return vector<decltype(cont)>(x, cont);
}

struct UnionFind {
  vector<int> par;
  vector<map<int, int>> mp;
  UnionFind(int n = 0) : par(n, -1){};
  int find(int x) {
    if (par[x] < 0) return x;
    return par[x] = find(par[x]);
  }
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);

    for (auto [key, val] : mp[y]) {
      mp[x][key] += val;
    }
    mp[y].clear();
    par[x] += par[y];
    par[y] = x;
    return true;
  }
  bool same(int x, int y) { return find(x) == find(y); }
  int size(int x) { return -par[find(x)]; }
};

int main() {
  int n, q;
  cin >> n >> q;
  UnionFind t(n);
  repeat(i, n) {
    int c;
    cin >> c;
    t.mp[i][c] = 1;
  }
  repeat(qi, q) {
    int type;
    cin >> type;
    if (type == 1) {
      int a, b;
      cin >> a >> b;
      --a, --b;
      t.unite(a, b);
    } else {
      int x, y;
      cin >> x >> y;
      --x;
      x = t.find(x);
      int ans = t.mp[x][y];
      cout << ans << endl;
    }
  }
  return 0;
}