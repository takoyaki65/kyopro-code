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
#include <random>
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

// S[i] := A[i] + A[i+1] (確定しないなら-1)
long long S[100005];

int main() {
  int N, Q;
  cin >> N >> Q;

  memset(S, -1, sizeof(S));
  UnionFind uf(N + 10);

  while (Q--) {
    int t, x, y, v;
    cin >> t >> x >> y >> v;
    --x, --y;
    if (t == 0) {
      S[x] = v;
      uf.unite(x, x + 1);
    } else {
      if (uf.same(x, y)) {
        long long val = v;
        int cur = x;
        if (cur < y) {
          // A[cur] = v
          // A[cur] + A[cur+1] = S[cur]
          // A[cur+1] = S[cur] - A[cur]
          while (cur < y) {
            val = S[cur] - val;
            cur += 1;
          }
        } else if (y < cur) {
          // A[cur] = v
          // A[cur-1] + A[cur] = S[cur-1]
          // A[cur-1] = S[cur-1] - A[cur]
          while (y < cur) {
            val = S[cur - 1] - val;
            cur -= 1;
          }
        }
        cout << val << endl;
      } else {
        cout << "Ambiguous" << endl;
      }
    }
  }

  return 0;
}