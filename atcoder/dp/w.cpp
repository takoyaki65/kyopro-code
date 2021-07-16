#include <algorithm>
#include <array>
#include <bitset>
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
#define bit_stand(n, k) ((n >> k) & 1)
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

  void set(int i, X x) {
    X val = query(i, i + 1);
    update(i, i + 1, -val + x);
  }

  X get(int i) { return query(i, i + 1); }

  void print() {
    for (int i = 0; i < n; ++i) {
      cout << get(i) << " ";
    }
    cout << endl;
  }
};

int N, M;
vector<tuple<int, int, int>> rla;
using X_type = long long;
using M_type = long long;
auto fx = [](X_type x1, X_type x2) -> X_type { return max(x1, x2); };
auto fa = [](X_type x, M_type m) -> X_type { return x + m; };
auto fm = [](M_type m1, M_type m2) -> M_type { return m1 + m2; };
const X_type ex = 0;
const M_type em = 0;
LazySegmentTree<X_type, M_type> dp(200005, fx, fa, fm, ex, em);

int main() {
  cin >> N >> M;
  repeat(i, M) {
    int l, r, a;
    cin >> l >> r >> a;
    --l, --r;
    rla.push_back({r, l, a});
  }
  sort(rla.rbegin(), rla.rend());

  repeat(i, N) {
    long long val = dp.query(0, i);
    long long dpi = dp.get(i);
    dp.update(i, i + 1, -dpi + val);
    while (rla.size() > 0) {
      auto [r, l, a] = rla.back();
      if (r != i)
        break;
      rla.pop_back();
      dp.update(l, r + 1, a);
    }
    // cout << "i: " << i << endl;
    // for (int i = 0; i < N; ++i) {
    //   cout << dp.get(i) << " ";
    // }
    // cout << endl;
  }

  cout << dp.query(0, N) << endl;
  return 0;
}