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

template <typename T>
struct SegmentTree {
  using F = function<T(T, T)>;

 private:
  int n;
  vector<T> node;
  F f;
  T e;

 public:
  SegmentTree(vector<T> v, T _e, F _f) : e(_e), f(_f) {
    int sz = v.size();
    n = 1;
    while (n < sz) n *= 2;
    node.resize(2 * n - 1, e);
    for (int i = 0; i < sz; ++i) node[i + n - 1] = v[i];
    for (int i = n - 2; i >= 0; --i)
      node[i] = f(node[2 * i + 1], node[2 * i + 2]);
  }

  void update(int x, T val) {
    x += (n - 1);

    node[x] = val;
    while (x > 0) {
      x = (x - 1) / 2;
      node[x] = f(node[2 * x + 1], node[2 * x + 2]);
    }
  }

  T get(int pos) { return node[pos + n - 1]; }

  // 区間[a, b)の結合
  // k := 自分がいるノードのインデックス
  // [l, r) := ノードkに対応する区間
  T query(int a, int b, int k = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;

    if (r <= a || b <= l) return e;

    if (a <= l && r <= b) return node[k];

    T vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
    T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
    return f(vl, vr);
  }
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> va(n);
  repeat(i, n) cin >> va[i];

  // initialize segment tree
  auto xor_func = [](int lv, int rv) -> int { return lv ^ rv; };
  SegmentTree<int> sgtree(va, 0, xor_func);

  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    --x;
    if (t == 1) {
      int val = sgtree.get(x);
      sgtree.update(x, xor_func(val, y));
    } else {
      cout << sgtree.query(x, y) << endl;
    }
  }
  return 0;
}