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