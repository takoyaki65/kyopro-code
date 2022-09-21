#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
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

  friend vec_i operator*(int k, const vec_i& rhs) { return rhs * k; }

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
    return abs(y - rhs.y) < eps ? true : y < rhs.y;
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
  static Rot RotDeg(double _deg) { return Rot(_deg * pi / 180.0); }
  static Rot RotRad(double _rad) { return Rot(_rad); }

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

/**
 * @brief 点群pointsの凸法を計算する
 *
 * @tparam Int 整数型(int, long longなど)
 */
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

struct ConvexHull_d {
  vector<vec_d> points;
  ConvexHull_d() {}

  void build() {
    vec_d pivot(0, 0);
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

    auto angleCmp = [&pivot](const vec_d& a, const vec_d& b) -> bool {
      // special case: if collinear, choose closet to pivot;
      if (collinear(pivot, a, b))  // special case
        return (a - pivot).length2() < (b - pivot).length2();

      return (a - pivot).cross(b - pivot) > 0;
    };
    sort(++points.begin(), points.end(), angleCmp);

    // S holds the Convex Hull
    // We initialize it with first three points
    vector<vec_d> S;
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
};

int main() {
  vector<vec_i<int>> abcd(4);
  cin >> abcd[0].x >> abcd[0].y >> abcd[1].x >> abcd[1].y >> abcd[2].x >>
      abcd[2].y >> abcd[3].x >> abcd[3].y;

  ConvexHull_i<int> ch;
  ch.points = abcd;
  ch.build();

  // for (auto p : ch.points) {
  //   cout << p.x << "," << p.y << endl;
  // }
  if (ch.points.size() != 5) {
    cout << "No" << endl;
    return 0;
  }
  for (int i = 0; i < 4; ++i) {
    bool ok = true;
    for (int j = 0; j < 4; ++j) {
      if (ch.points[(i + j) % 4] != abcd[j]) {
        ok = false;
        break;
      }
    }
    if (ok) {
      cout << "Yes" << endl;
      return 0;
    }
  }

  cout << "No" << endl;
  return 0;
}