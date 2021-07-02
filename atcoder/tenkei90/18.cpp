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

const double eps = 1e-9;
const double pi = acos(-1.0);

// a > 0ならば+1, a == 0ならば0, a <
// 0ならば-1　を返す。　基本的にEPS込みの評価はこれで行う。
//不等式は、加減算に直してこれに適用する。
int sgn(const double a) {
  return (a < -eps ? -1 : (a > eps ? +1 : 0));
}

struct vec3d {
  double x, y, z;
  vec3d() : x(0.0), y(0.0), z(0.0) {}
  vec3d(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
  vec3d(const vec3d& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
  double& operator[](int idx) { return ((double*)(&x))[idx]; }
  double operator[](int idx) const { return ((double*)(&x))[idx]; }
  bool operator==(const vec3d& rhs) const {
    return abs(x - rhs.x) <= eps && abs(y - rhs.y) <= eps &&
           abs(z - rhs.z) <= eps;
  }
  bool operator!=(const vec3d& rhs) const { return !(*this).operator==(rhs); }
  bool operator<(const vec3d& rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y) ||
           (x == rhs.x && y == rhs.y && z < rhs.z);
  }
  vec3d& operator-=(const vec3d& rhs) {
    x -= rhs.x, y -= rhs.y, z -= rhs.z;
    return *this;
  }
  vec3d& operator+=(const vec3d& rhs) {
    x += rhs.x, y += rhs.y, z += rhs.z;
    return *this;
  }
  vec3d& operator*=(double k) {
    x *= k, y *= k, z *= k;
    return *this;
  }
  vec3d operator+(const vec3d& rhs) const { return vec3d(*this) += rhs; }
  vec3d operator-(const vec3d& rhs) const { return vec3d(*this) -= rhs; }
  vec3d operator*(double k) const { return vec3d(*this) *= k; }

  vec3d cross(const vec3d& rhs) const {
    return vec3d(y * rhs.z - rhs.y * z, z * rhs.x - rhs.z * x,
                 x * rhs.y - rhs.x * y);
  }

  double dot(const vec3d& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

  double length2() const { return x * x + y * y + z * z; }

  friend ostream& operator<<(ostream& os, const vec3d& p) {
    return os << p.x << " " << p.y << " " << p.z;
  }
};

double T, L, X, Y;

vec3d CalcCoordinate(int t) {
  vec3d ret;
  ret.x = 0.0;
  ret.y = -L * sin(2 * pi * t / T) / 2.0;
  ret.z = (L - L * cos(2 * pi * t / T)) / 2.0;
  return ret;
}

int main() {
  cin >> T >> L >> X >> Y;

  vec3d chokudai(X, Y, 0.0);

  int q;
  cin >> q;
  while (q--) {
    int e;
    cin >> e;
    vec3d pos = CalcCoordinate(e);
    vec3d vd = pos - chokudai;
    double dz = vd.z;
    double dr = sqrt(vd.x * vd.x + vd.y * vd.y);
    double ans = atan2(dz, dr) * 180.0 / pi;
    cout << fixed << setprecision(10) << ans << endl;
  }

  return 0;
}