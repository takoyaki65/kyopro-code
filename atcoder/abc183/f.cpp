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
inline int sz(T &x) {
    return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool setmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

// https://ei1333.github.io/luzhiled/snippets/structure/union-find.html
struct UnionFind {
    vector<int> data;
    // cls[i][class] := 生徒iと合流している生徒のうち、クラスclassに属している生徒の数
    vector<map<int,int>> cls;
    vector<int> c_vec;

    UnionFind(int sz, const vector<int> c_array_) : cls(sz), c_vec(c_array_) {
        data.assign(sz, -1);
        for(int i = 0; i < sz; ++i) {
          cls[i][c_vec[i]] = 1;
        }
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return (false);
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;

        // clsのマージ
        for(auto &pii : cls[y]) {
          auto [class_, num] = pii;
          cls[x][class_] += num;
        }

        cls[y].clear();

        return (true);
    }

    int find(int k) {
        if (data[k] < 0) return (k);
        return (data[k] = find(data[k]));
    }

    int query2(int x, int class_) {
      return cls[find(x)][class_];
    }

    int size(int k) {
        return (-data[find(k)]);
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> c_vec(n);
  repeat(i, n) {
    cin >> c_vec[i];
    --c_vec[i];
  }
  UnionFind uf(n, c_vec);
  repeat(_, q) {
    int query_type;
    cin >> query_type;
    if(query_type == 1) {
      int a, b;
      cin >> a >> b;
      --a, --b;
      uf.unite(a, b);
    } else {
      int x, y;
      cin >> x >> y;
      --x, --y;
      cout << uf.query2(x, y) << endl;
    }
  }
  return 0;
}