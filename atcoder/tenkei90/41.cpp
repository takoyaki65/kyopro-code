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

  Int cross(vec_i rhs) const { return x * rhs.y - y * rhs.x; }

  Int dot(vec_i rhs) const { return x * rhs.x + y * rhs.y; }

  Int length2() const { return x * x + y * y; }

  friend ostream& operator<<(ostream& os, const vec_i& p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }
};

template <typename Int>
Int dot(vec_i<Int> a, vec_i<Int> b) {
  return a.x * b.x + a.y * b.y;
}

template <typename Int>
double dist(vec_i<Int> a, vec_i<Int> b) {
  return hypot(a.x - b.x, a.y - b.y);
}

template <typename Int>
bool ccw(vec_i<Int> p, vec_i<Int> q, vec_i<Int> r) {
  return (q - p).cross(r - p) > 0;
}

template <typename Int>
bool collinear(vec_i<Int> p, vec_i<Int> q, vec_i<Int> r) {
  return (q - p).cross(r - p) == 0;
}

template <typename Int>
double areaTri(vec_i<Int> a, vec_i<Int> b, vec_i<Int> c) {
  return abs((b - a).cross(c - a)) / 2.0;
}

template <typename Int>
struct ConvexHull_i {
  using vec_type = vec_i<Int>;
  vector<vec_type> points;
  ConvexHull_i() {}

  void build() {
    vec_type pivot(0, 0);
    int i, j, n = (int)points.size();
    // Special Case: Polygon with 3 points
    if (n <= 3) {
      if (!(points[0] == points[n - 1]))
        points.push_back(points[0]);
      return;
    }

    // Find Initial Point: Low Y then Right X
    int P0 = 0;
    for (int i = 0; i < n; ++i) {
      if (points[i].y < points[P0].y ||
          (points[i].y == points[P0].y && points[i].x > points[P0].x))
        P0 = i;
    }

    swap(points[0], points[P0]);

    // second, sort points by angle with pivot P0
    pivot = points[0];

    auto angleCmp = [&pivot](const vec_type& a, const vec_type& b) -> bool {
      // special case: if collinear, choose closet to pivot;
      if (collinear(pivot, a, b))  // special case
        return (a - pivot).length2() < (b - pivot).length2();

      return (a - pivot).cross(b - pivot) > 0;
    };
    sort(++points.begin(), points.end(), angleCmp);

    // S holds the Convex Hull
    // We initialize it with first three points
    vector<vec_type> S;
    S.push_back(points[n - 1]);
    S.push_back(points[0]);
    S.push_back(points[1]);

    // We start on the third point
    i = 2;
    while (i < n) {
      j = (int)S.size() - 1;
      // If the next point is left of CH, keep it.
      // Else, pop the last CH point and try again.

      // j <= 1 : 得られる点群が全て一直線の場合、
      //          お互い最も遠い位置に属する2点(points[0]とpoints[1])
      //          も削除してしまうため、それを防ぐ
      //          (常に3点は含むようにする)
      if (j <= 1 || ccw(S[j - 1], S[j], points[i]))
        S.push_back(points[i++]);
      else
        S.pop_back();
    }

    points = S;
    return;
  }

  double area() {
    double result = 0.0;
    for (int i = 0; i < (int)points.size() - 1; ++i) {
      result += points[i].cross(points[i + 1]);
    }
    return abs(result) / 2.0;
  }

  Int area2() {
    Int result = 0;
    for (int i = 0; i < (int)points.size() - 1; ++i) {
      result += points[i].cross(points[i + 1]);
    }
    return abs(result);
  }
};

/* ピックの定理
 * S = i + b/2 - 1
 * S := 多角形の面積
 * i := 境界を除いた多角形の内部にある格子点の個数
 * b := 辺上にある格子点の個数
 *
 * i を求めるには
 * 2S = 2i + b - 2
 * i = (2S - b + 2)/2
 *
 * 全部合わせると、
 * i + b = (2S + b + 2)/2
 */

using vec_l = vec_i<long long>;

const long long lmax = 9223372036854775807LL;

int main() {
  int N;
  cin >> N;
  vector<vec_l> points(N);
  repeat(i, N) cin >> points[i].x >> points[i].y;

  bool all_colinear = true;
  repeat(i, N) if (!collinear(points[i], points[(i + 1) % N],
                              points[(i + 2) % N])) all_colinear = false;

  if (all_colinear) {
    // 例外
    // ピックの定理が成り立たないので、
    // 辺上の格子点の数を調べる
    long long lx = 10000000000000LL, rx = -1LL, ly = 100000000000000LL,
              ry = -1LL;

    repeat(i, N) {
      lx = min(lx, points[i].x), rx = max(rx, points[i].x),
      ly = min(ly, points[i].y), ry = max(ry, points[i].y);
    }

    if (lx == rx) {
      swap(lx, ly);
      swap(rx, ry);
    }

    long long ans = rx - lx + 1 - N;
    cout << ans << endl;
    return 0;
  }

  ConvexHull_i<long long> CH;
  CH.points = points;
  CH.build();

  long long S2 = CH.area2();

  const int vertex_num = CH.points.size();
  // assert(CH.points[vertex_num - 1] == CH.points[0]);

  // cout << "Convex_hull : " << endl;
  // for (int i = 0; i < vertex_num; ++i) {
  //   cout << CH.points[i] << endl;
  // }

  // for (int i = 0; i < vertex_num - 1; ++i) {
  //   cout << "S_" << i << " = " << CH.points[i].cross(CH.points[i + 1]) <<
  //   endl;
  // }

  long long b = 0;
  for (int i = 1; i < vertex_num; ++i) {
    const vec_l& p1 = CH.points[i - 1];
    const vec_l& p2 = CH.points[i];
    vec_l dp = (p2 - p1);
    b += gcd(abs(dp.x), abs(dp.y));
  }

  // // cout << "S2: " << S2 << endl;
  // // cout << "b: " << b << endl;

  long long ans = (S2 + b + 2LL) / 2LL - N;

  cout << ans << endl;
  return 0;
}