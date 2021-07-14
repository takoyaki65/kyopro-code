#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct SegmentTree {
  using F = function<T(const T&, const T&)>;

 private:
  int n;
  vector<T> dat, lazy;
  F f;
  T e;

  /* lazy eval */
  void eval(int k) {
    if (lazy[k] == e)  // 更新するものが無ければ終了
      return;
    if (k < n - 1) {  // 葉で無ければ子に伝搬
      lazy[k * 2 + 1] = lazy[k];
      lazy[k * 2 + 2] = lazy[k];
    }
    // 自身を更新
    dat[k] = lazy[k];
    lazy[k] = e;
  }

  void update(int a, int b, int x, int k, int l, int r) {
    eval(k);
    if (a <= l && r <= b) {  // 完全に内側のとき
      lazy[k] = x;
      eval(k);
    } else if (a < r && l < b) {  // 一部区間が被るとき
      update(a, b, x, k * 2 + 1, l, (l + r) / 2);  // 左の子
      update(a, b, x, k * 2 + 2, (l + r) / 2, r);  // 右の子
      dat[k] = f(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  T query_sub(int a, int b, int k, int l, int r) {
    eval(k);
    if (r <= a || b <= l) {  // 完全に外側のとき
      return e;
    } else if (a <= l && r <= b) {  // 完全に内側のとき
      return dat[k];
    } else {  // 一部区間が被るとき
      T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
      T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
      return f(vl, vr);
    }
  }

 public:
  SegmentTree(int n_, T e_, F f_)
      : n(), e(e_), dat(n_ * 4, e_), lazy(n_ * 4, e_), f(f_) {
    int x = 1;
    while (n_ > x)
      x <<= 1;
    n = x;
  }

  void update(int i, T x) {
    i += n - 1;
    dat[i] = x;
    while (i > 0) {
      i = (i - 1) / 2;  // parent
      dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
  }

  void update(int a, int b, int x) { update(a, b, x, 0, 0, n); }

  T get(int pos) { return dat[pos + n - 1]; }

  T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
};
