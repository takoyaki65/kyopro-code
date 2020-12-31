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
  int h{}, w{}, m{};
  cin >> h >> w >> m;
  int x[m], y[m];
  repeat(i, m) {
    cin >> x[i] >> y[i];
    --x[i], --y[i];
  }

  // vh[x] := x行目のマスで,最も左端に近い障害物のマスの間のマスの数
  // vw[y] := y列目のマスで,最も上端に近い障害物のマスの間のマスの数
  vector<int> vh(h, w);
  vector<int> vw(w, h);
  repeat(i, m) {
    setmin(vh[x[i]], y[i]);
    setmin(vw[y[i]], x[i]);
  }

  // vh_b[x] := x行目のマスにある障害物のy座標の配列
  auto vh_b = vectors(0, h, 0);
  repeat(i, m) { vh_b[x[i]].push_back(y[i]); }

  long long ans = 0;
  repeat(y, vh[0]) ans += vw[y];
  repeat(x, vw[0]) ans += vh[x];

  auto plus_func = [](int l, int r) -> int { return l + r; };
  vector<int> bvec(w, 0);
  repeat(y, vh[0]) bvec[y] = 1;
  SegmentTree<int> sgtree(bvec, 0, plus_func);

  repeat(x, vw[0]) {
    ans -= sgtree.query(0, vh[x]);
    for (const int& y : vh_b[x]) {
      sgtree.update(y, 0);
    }
  }
  cout << ans << endl;
  return 0;
}