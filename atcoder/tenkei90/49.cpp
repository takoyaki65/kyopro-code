#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
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

struct Edge {
  int from, to, cost;
  bool operator<(const Edge& rhs) { return cost < rhs.cost; }
};

int N, M;
Edge E[100005];

int main() {
  cin >> N >> M;
  // N+1頂点のグラフ
  repeat(i, M) {
    int c, l, r;
    cin >> c >> l >> r;
    E[i] = {l - 1, r, c};
  }

  sort(E, E + M);
  long long ans = 0;
  UnionFind uf(N + 1);
  repeat(i, M) {
    auto [from, to, cost] = E[i];
    if (!uf.same(from, to)) {
      uf.unite(from, to);
      ans += cost;
    }
  }

  // 連結性判定
  repeat_from(i, 1, N + 1) {
    if (!uf.same(i - 1, i)) {
      cout << -1 << endl;
      return 0;
    }
  }

  cout << ans << endl;
  return 0;
}