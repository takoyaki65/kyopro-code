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