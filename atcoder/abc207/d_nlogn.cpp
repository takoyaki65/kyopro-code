// https://atcoder.jp/contests/abc207/editorial/2167
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

template <typename Int>
struct vec_i {
  Int x, y;
  vec_i() : x(0), y(0) {}
  vec_i(Int _x, Int _y) : x(_x), y(_y) {}
  vec_i(const vec_i& rhs) : x(rhs.x), y(rhs.y) {}
  Int& operator[](int idx) { return ((Int*)(&x))[idx]; }
  Int operator[](int idx) const { return ((Int*)(&x))[idx]; }
  bool operator==(const vec_i& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(const vec_i& rhs) const { return !(*this).operator==(rhs); }
  bool operator<(const vec_i& rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
    // return sgn(rhs.x - x) > 0 || (sgn(rhs.x - x) == 0 && sgn(rhs.y - y) > 0);
  }
  vec_i& operator-=(const vec_i& rhs) {
    x -= rhs.x, y -= rhs.y;
    return *this;
  }
  vec_i& operator+=(const vec_i& rhs) {
    x += rhs.x, y += rhs.y;
    return *this;
  }
  vec_i& operator*=(int k) {
    x *= k, y *= k;
    return *this;
  }
  vec_i operator+(const vec_i& rhs) const { return vec_i(*this) += rhs; }
  vec_i operator-(const vec_i& rhs) const { return vec_i(*this) -= rhs; }
  vec_i operator*(int k) const { return vec_i(*this) *= k; }

  friend vec_i operator*(int k, const vec_i& rhs) { return rhs * k; }

  Int cross(vec_i rhs) const { return x * rhs.y - y * rhs.x; }

  Int dot(vec_i rhs) const { return x * rhs.x + y * rhs.y; }

  Int length2() const { return x * x + y * y; }

  friend ostream& operator<<(ostream& os, const vec_i& p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }
};

template <typename Int>
bool collinear(vec_i<Int> p, vec_i<Int> q, vec_i<Int> r) {
  return (q - p).cross(r - p) == 0;
}

/**
 * @brief Z-algorithm
 *
 * @ref snuke https://snuke.hatenablog.com/entry/2014/12/03/214243
 *
 * @param S 配列
 * @param Z Z-array Z[i] = len: Z[0:len)とZ[i:i+len)が一致する
 */
void Zarray(const vector<int>& S, vector<int>& Z) {
  const int n = S.size();
  if (Z.size() != n)
    Z.assign(n, 0);
  Z[0] = n;
  // i := 現在見ている文字の先頭
  // j := 共通接頭辞の長さ
  int i = 1, j = 0;
  while (i < n) {
    while (i + j < n && S[j] == S[i + j])
      j += 1;
    Z[i] = j;
    if (j == 0) {
      i += 1;
      continue;
    }
    int k = 1;
    while (i + k < n && k + Z[k] < j)
      Z[i + k] = Z[k], k += 1;
    i += k;
    j -= k;
  }
}

vector<int> pts_to_str(const vector<vec_i<int>>& pts) {
  const int N = pts.size();
  vector<int> ret(3 * N);
  repeat(i, N) {
    ret[3 * i] = pts[i].length2();
    ret[3 * i + 1] = pts[i].dot(pts[(i + 1) % N]);
    ret[3 * i + 2] = pts[i].cross(pts[(i + 1) % N]);
  }
  return ret;
}

int main() {
  int N;
  cin >> N;
  vector<vec_i<int>> pa(N), pb(N);
  repeat(i, N) cin >> pa[i].x >> pa[i].y;
  repeat(i, N) cin >> pb[i].x >> pb[i].y;

  if (N == 1) {
    cout << "Yes" << endl;
    return 0;
  }

  {
    vec_i<int> g(0, 0);
    repeat(i, N) g += pa[i];
    repeat(i, N) pa[i] = N * pa[i] - g;
    g = vec_i<int>(0, 0);
    repeat(i, N) g += pb[i];
    repeat(i, N) pb[i] = N * pb[i] - g;
  }

  repeat(i, N) {
    if (pa[i] == vec_i<int>{0, 0}) {
      // 0点を削除
      pa.erase(pa.begin() + i);
      break;
    }
  }
  repeat(i, N) {
    if (pb[i] == vec_i<int>{0, 0}) {
      pb.erase(pb.begin() + i);
      break;
    }
  }
  if (pa.size() != pb.size()) {
    cout << "No" << endl;
    return 0;
  }

  N = pa.size();

  auto angleCmp = [](const vec_i<int>& lhs, const vec_i<int>& rhs) -> bool {
    double La = atan2(lhs.y, lhs.x), Ra = atan2(rhs.y, rhs.x);
    return (La != Ra) ? La < Ra : lhs.length2() < rhs.length2();
  };

  sort(pa.begin(), pa.end(), angleCmp);
  sort(pb.begin(), pb.end(), angleCmp);

  // cout << "pa: " << endl;
  // repeat(i, N) cout << pa[i] << endl;
  // cout << "pb: " << endl;
  // repeat(i, N) cout << pb[i] << endl;

  vector<int> va = pts_to_str(pa);
  vector<int> vb = pts_to_str(pb);

  // cout << "va: " << endl;
  // for (const int& v : va)
  //   cout << v << " ";
  // cout << endl;
  // cout << "vb: " << endl;
  // for (const int& v : vb)
  //   cout << v << " ";
  // cout << endl;

  vector<int> Zstr;
  Zstr.insert(Zstr.end(), va.begin(), va.end());
  Zstr.insert(Zstr.end(), vb.begin(), vb.end());
  Zstr.insert(Zstr.end(), vb.begin(), vb.end());

  // cout << "Zstr " << endl;
  // for (const int& v : Zstr)
  //   cout << v << " ";
  // cout << endl;

  vector<int> vZ;
  Zarray(Zstr, vZ);
  // for (int i = 0; i < 12 * N + 1; ++i) {
  //   cout << "vZ[" << i << "] = " << vZ[i] << endl;
  // }

  // cout << endl;

  string ans = "No";
  for (int i = 3 * N; i < 6 * N; i += 3) {
    // cout << "vZ[" << i << "] = " << vZ[i] << endl;
    if (vZ[i] >= 3 * N) {
      ans = "Yes";
      break;
    }
  }

  cout << ans << endl;

  return 0;
}