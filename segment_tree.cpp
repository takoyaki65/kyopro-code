#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 遅延評価無しのセグメント木
 *        参考: https://algo-logic.info/segment-tree/#toc_id_3
 *
 * @tparam T 集合Tのモノイド
 */
template <typename T>
struct SegmentTree {
  using F = function<T(const T&, const T&)>;

 private:
  int n;
  vector<T> dat;
  F f;
  T e;

  T query_sub(int a, int b, int k, int l, int r) {
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
  /**
   * @brief Construct a new Segment Tree object
   *
   * @param n_ 配列のサイズ
   * @param e_ 単位元
   * @param f_ 二項演算 T f_ T -> T
   */
  SegmentTree(int n_, T e_, F f_) : n(), e(e_), dat(n_ * 4, e_), f(f_) {
    int x = 1;
    while (n_ > x)
      x <<= 1;
    n = x;
  }

  /**
   * @brief Construct a new Segment Tree object
   *        構築O(n)
   * @param v  配列
   * @param e_ 単位元
   * @param f_ 二項演算
   */
  SegmentTree(const vector<T> v, T e_, F f_)
      : n(), e(e_), f(f_), dat(v.size() * 4, e_) {
    int x = 1;
    while (v.size() > x)
      x <<= 1;
    n = x;
    for (int i = 0; i < v.size(); ++i) {
      dat[i + n - 1] = v[i];
    }
    for (int k = n - 2; k >= 0; --k) {
      dat[k] = f(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }

  // i番目をxに更新 O(log(n))
  void update(int i, T x) {
    i += n - 1;
    dat[i] = x;
    while (i > 0) {
      i = (i - 1) / 2;  // parent
      dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
  }

  // i番目の値を取得
  T get(int pos) { return dat[pos + n - 1]; }

  // 区間[a,b)全てに二項演算fを作用させた値を取得.O(log(n))
  T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
};
