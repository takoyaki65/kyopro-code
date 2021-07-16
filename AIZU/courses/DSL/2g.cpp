#include <bits/stdc++.h>
using namespace std;

template <typename X, typename M>
struct LazySegTreeProportional {
  using FX = function<X(X, X)>;
  using FA = function<X(X, M)>;
  using FM = function<M(M, M)>;
  using FP = function<M(M, long long)>;

 private:
  int n;
  FX fx;
  FA fa;
  FM fm;
  FP fp;
  const X ex;
  const M em;
  vector<X> dat;
  vector<M> lazy;

  /* lazy eval */
  void eval(int k, int len) {
    if (lazy[k] == em)  // 更新するものが無ければ終了
      return;
    if (k < n - 1) {  // 葉でなければ子に伝搬
      lazy[k * 2 + 1] = fm(lazy[k * 2 + 1], lazy[k]);
      lazy[k * 2 + 2] = fm(lazy[k * 2 + 2], lazy[k]);
    }
    // 自身を更新
    dat[k] = fa(dat[k], fp(lazy[k], len));
    lazy[k] = em;
  }

  void update_sub(int a, int b, M x, int k, int l, int r) {
    eval(k, r - l);
    if (a <= l && r <= b) {  // 完全に内側のとき
      lazy[k] = fm(lazy[k], x);
      eval(k, r - l);
    } else if (a < r && l < b) {  // 一部区間が被るとき
      update_sub(a, b, x, k * 2 + 1, l, (l + r) / 2);
      update_sub(a, b, x, k * 2 + 2, (l + r) / 2, r);
      dat[k] = fx(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  X query_sub(int a, int b, int k, int l, int r) {
    eval(k, r - l);
    if (r <= a || b <= l) {  // 完全に外側のとき
      return ex;
    } else if (a <= l && r <= b) {  // 完全に内側のとき
      return dat[k];
    } else {  // 一部区間が被るとき
      X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
      X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
      return fx(vl, vr);
    }
  }

 public:
  LazySegTreeProportional(int n_, FX fx_, FA fa_, FM fm_, FP fp_, X ex_, M em_)
      : n(),
        fx(fx_),
        fa(fa_),
        fm(fm_),
        fp(fp_),
        ex(ex_),
        em(em_),
        dat(n_ * 4, ex),
        lazy(n_ * 4, em) {
    int x = 1;
    while (n_ > x)
      x *= 2;
    n = x;
  }

  LazySegTreeProportional(const vector<X>& v,
                          FX fx_,
                          FA fa_,
                          FM fm_,
                          FP fp_,
                          X ex_,
                          M em_)
      : n(),
        fx(fx_),
        fa(fa_),
        fm(fm_),
        fp(fp_),
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
};

// 区間加算、区間和
using X = long long;
using M = long long;
auto fx = [](X x1, X x2) -> X { return x1 + x2; };
auto fa = [](X x, M m) -> X { return x + m; };
auto fm = [](M m1, M m2) -> M { return m1 + m2; };
auto fp = [](M m, long long n) -> M { return m * n; };
const long long ex = 0;
const long long em = 0;

int main() {
  int n, q;
  cin >> n >> q;
  LazySegTreeProportional<X, M> raq(n, fx, fa, fm, fp, ex, em);

  while (q--) {
    int cmd;
    cin >> cmd;
    if (cmd == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      --s;
      raq.update(s, t, x);
    } else {
      int s, t;
      cin >> s >> t;
      --s;
      cout << raq.query(s, t) << endl;
    }
  }
  return 0;
}