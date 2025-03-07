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

const double eps = 1e-4;
const double pi = acos(-1.0);

// a > 0ならば+1, a == 0ならば0, a <
// 0ならば-1　を返す。　基本的にEPS込みの評価はこれで行う。
//不等式は、加減算に直してこれに適用する。
int sgn(const double a) {
  return (a < -eps ? -1 : (a > eps ? +1 : 0));
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

struct vec_d {
  double x, y;
  vec_d() : x(0), y(0) {}
  vec_d(double _x, double _y) : x(_x), y(_y) {}
  vec_d(const vec_d& rhs) : x(rhs.x), y(rhs.y) {}
  double& operator[](int idx) { return ((double*)(&x))[idx]; }
  double operator[](int idx) const { return ((double*)(&x))[idx]; }
  bool operator==(const vec_d& rhs) const {
    return abs(x - rhs.x) < eps && abs(y - rhs.y) < eps;
  }
  bool operator!=(const vec_d& rhs) const { return !(*this).operator==(rhs); }
  bool operator<(const vec_d& rhs) const {
    if (abs(x - rhs.x) > eps)
      return x < rhs.x;
    return y < rhs.y;
  }
  bool operator<=(const vec_d& rhs) const {
    if (abs(x - rhs.x) > eps)
      return x < rhs.x;
    return y <= rhs.y;
  }
  bool operator>(const vec_d& rhs) const { return !(*this).operator<=(rhs); }
  bool operator>=(const vec_d& rhs) const { return !(*this).operator<(rhs); }
  vec_d& operator-=(const vec_d& rhs) {
    x -= rhs.x, y -= rhs.y;
    return *this;
  }
  vec_d& operator+=(const vec_d& rhs) {
    x += rhs.x, y += rhs.y;
    return *this;
  }
  vec_d& operator*=(double k) {
    x *= k, y *= k;
    return *this;
  }
  vec_d& operator/=(double k) {
    x /= k, y /= k;
    return *this;
  }
  vec_d operator+(const vec_d& rhs) const { return vec_d(*this) += rhs; }
  vec_d operator-(const vec_d& rhs) const { return vec_d(*this) -= rhs; }
  vec_d operator*(double k) const { return vec_d(*this) *= k; }
  vec_d operator/(double k) const { return vec_d(*this) /= k; }

  friend vec_d operator*(double k, const vec_d& rhs) { return rhs * k; }

  double cross(vec_d rhs) const { return x * rhs.y - y * rhs.x; }

  double dot(vec_d rhs) const { return x * rhs.x + y * rhs.y; }

  double length2() const { return x * x + y * y; }

  friend ostream& operator<<(ostream& os, const vec_d& p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }
};

class Rot {
 public:
  static Rot Deg(double _deg) { return Rot(_deg * pi / 180.0); }
  static Rot Rad(double _rad) { return Rot(_rad); }

  vec_d operator*(const vec_d& v) const {
    /* cos -sin   vx
     * sin  cos * vy
     */
    double C = cos(angle_in_radians), S = sin(angle_in_radians);
    return vec_d(C * v.x - S * v.y, S * v.x + C * v.y);
  }

 private:
  double angle_in_radians;
  Rot(double _rad) : angle_in_radians(_rad) {}
};

template <typename Int>
Int dot(vec_i<Int> a, vec_i<Int> b) {
  return a.x * b.x + a.y * b.y;
}

double dot(vec_d a, vec_d b) {
  return a.x * b.x + a.y * b.y;
}

template <typename Int>
double dist(vec_i<Int> a, vec_i<Int> b) {
  return hypot(a.x - b.x, a.y - b.y);
}

double dist(vec_d a, vec_d b) {
  return hypot(a.x - b.x, a.y - b.y);
}

template <typename Int>
bool ccw(vec_i<Int> p, vec_i<Int> q, vec_i<Int> r) {
  return (q - p).cross(r - p) > 0;
}

bool ccw(vec_d p, vec_d q, vec_d r) {
  return (q - p).cross(r - p) > 0.0;
}

template <typename Int>
bool collinear(vec_i<Int> p, vec_i<Int> q, vec_i<Int> r) {
  return (q - p).cross(r - p) == 0;
}

bool collinear(vec_d p, vec_d q, vec_d r) {
  return abs((q - p).cross(r - p)) < eps;
}

template <typename Int>
double areaTri(vec_i<Int> a, vec_i<Int> b, vec_i<Int> c) {
  return abs((b - a).cross(c - a)) / 2.0;
}

double areaTri(vec_d a, vec_d b, vec_d c) {
  return abs((b - a).cross(c - a)) / 2.0;
}

// Given points a, b, p, calculate distance from p to line ab.
double distToLine(vec_d p, vec_d a, vec_d b, vec_d& c) {
  // point c: c = a + u * |ab|
  vec_d ap = p - a, ab = b - a;

  // dot product calculates size of ap in ab
  // norm square will calculate the scale to ab
  double u = dot(ap, ab) / ab.length2();

  // translate a by u * |ab| to find point c.
  c = a + (ab * u);
  return dist(p, c);
}

int N;
vec_d pa[110], pb[110];
bool used[110];

int main() {
  cin >> N;
  repeat(i, N) cin >> pa[i].x >> pa[i].y;
  repeat(i, N) cin >> pb[i].x >> pb[i].y;

  {
    // それぞれの重心を引く
    vec_d g(0, 0);
    repeat(i, N) g += pa[i];
    repeat(i, N) pa[i] = N * pa[i] - g;
    g = vec_d(0, 0);
    repeat(i, N) g += pb[i];
    repeat(i, N) pb[i] = N * pb[i] - g;
  }

  // ピボット点のx座標,y座標はなるべく0でない値にする
  repeat(i, N) {
    if (pa[i] != vec_d(0, 0)) {
      swap(pa[i], pa[0]);
    }
  }

  repeat(i, N) {
    double angle = atan2(pb[i].y, pb[i].x) - atan2(pa[0].y, pa[0].x);
    Rot rot = Rot::Rad(angle);
    memset(used, 0, sizeof(used));
    int cnt = 0;
    repeat(j, N) {
      vec_d pt = rot * pa[j];
      repeat(k, N) {
        if (pt == pb[k] && used[k] == false) {
          used[k] = true;
          cnt += 1;
          break;
        }
      }
    }
    if (cnt == N) {
      cout << "Yes" << endl;
      return 0;
    }
  }

  cout << "No" << endl;
  return 0;
}