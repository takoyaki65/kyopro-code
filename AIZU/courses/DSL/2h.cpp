#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 区間[0, n-1]の遅延評価セグメント木
 * 参考 https://algo-logic.info/segment-tree/#toc_id_6_2
 *
 * @tparam X 集合Xのモノイド(int, long long など)
 * @tparam M 集合Mのモノイド(int, long long など)
 */
template <typename X, typename M>
struct LazySegmentTree {
  using FX = function<X(X, X)>;
  using FA = function<X(X, M)>;
  using FM = function<M(M, M)>;

 private:
  int n;
  FX fx;
  FA fa;
  FM fm;
  const X ex;
  const M em;
  vector<X> dat;
  vector<M> lazy;

  /* lazy eval */
  void eval(int k) {
    if (lazy[k] == em)
      return;         // 更新するものがなければ終了
    if (k < n - 1) {  // 葉でなければ子に伝搬
      lazy[k * 2 + 1] = fm(lazy[k * 2 + 1], lazy[k]);
      lazy[k * 2 + 2] = fm(lazy[k * 2 + 2], lazy[k]);
    }
    // 自身を更新
    dat[k] = fa(dat[k], lazy[k]);
    lazy[k] = em;
  }

  void update_sub(int a, int b, M x, int k, int l, int r) {
    eval(k);
    if (a <= l && r <= b) {  // 完全に内側のとき
      lazy[k] = fm(lazy[k], x);
      eval(k);
    } else if (a < r && l < b) {  // 一部区間が被るとき
      update_sub(a, b, x, k * 2 + 1, l, (l + r) / 2);
      update_sub(a, b, x, k * 2 + 2, (l + r) / 2, r);
      dat[k] = fx(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  X query_sub(int a, int b, int k, int l, int r) {
    eval(k);
    if (r <= a || b <= l) {  // 完全に外側のとき
      return ex;
    } else if (a <= l && r <= b) {  // 完全に内側のとき
      return dat[k];
    } else {
      X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
      X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
      return fx(vl, vr);
    }
  }

 public:
  /**
   * @brief Construct a new Lazy Segment Tree object
   *
   * @param n_  配列のサイズ
   * @param fx_ 二項演算子  X fx_ X -> X
   * @param fa_ 二項演算子  X fa_ M -> X
   * @param fm_ 二項演算子  M fm_ M -> M
   * @param ex_ モノイドXの単位元
   * @param em_ モノイドMの単位元
   */
  LazySegmentTree(int n_, FX fx_, FA fa_, FM fm_, X ex_, M em_)
      : n(),
        fx(fx_),
        fa(fa_),
        fm(fm_),
        ex(ex_),
        em(em_),
        dat(n_ * 4, ex),
        lazy(n_ * 4, em) {
    int x = 1;
    while (n_ > x)
      x *= 2;
    n = x;
  }

  /**
   * @brief Construct a new Lazy Segment Tree object
   *
   * @param v   モノイドXの配列
   * @param fx_ 二項演算子  X fx_ X -> X
   * @param fa_ 二項演算子  X fa_ M -> X
   * @param fm_ 二項演算子  M fm_ M -> M
   * @param ex_ モノイドXの単位元
   * @param em_ モノイドMの単位元
   */
  LazySegmentTree(const vector<X>& v, FX fx_, FA fa_, FM fm_, X ex_, M em_)
      : n(),
        fx(fx_),
        fa(fa_),
        fm(fm_),
        ex(ex_),
        em(em_),
        dat(v.size() * 4, ex),
        lazy(v.size() * 4, em) {
    int x = 1;
    while (v.size() > x)
      x *= 2;
    n = x;
    for (int i = 0; i < v.size(); ++i)
      dat[i + n - 1] = v[i];
    for (int k = n - 2; k >= 0; --k)
      dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
  }

  void update(int a, int b, M x) { update_sub(a, b, x, 0, 0, n); }

  X query(int a, int b) { return query_sub(a, b, 0, 0, n); }

  X get(int i) { return query(i, i + 1); }

  void print() {
    for (int i = 0; i < n; ++i) {
      cout << get(i) << " ";
    }
    cout << endl;
  }
};

// 区間min, 区間add
using X_type = long long;
using M_type = long long;
auto fx = [](X_type x1, X_type x2) -> X_type { return min(x1, x2); };
auto fa = [](X_type x, M_type m) -> X_type { return x + m; };
auto fm = [](M_type m1, M_type m2) -> M_type { return m1 + m2; };
const X_type ex = numeric_limits<int>::max();
const M_type em = 0;

int main() {
  int n, q;
  cin >> n >> q;
  vector<long long> v(n, 0);
  LazySegmentTree<X_type, M_type> sgtree(v, fx, fa, fm, ex, em);
  while (q--) {
    int cmd;
    cin >> cmd;
    if (cmd == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      sgtree.update(s, t + 1, x);
    } else {
      int s, t;
      cin >> s >> t;
      cout << sgtree.query(s, t + 1) << endl;
    }
  }

  return 0;
}