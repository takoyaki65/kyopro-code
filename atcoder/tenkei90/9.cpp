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

struct Point {
  long long x, y;
  double cross(const Point& rhs) const { return x * rhs.y - y * rhs.x; }
  Point& operator-=(const Point& rhs) {
    this->x -= rhs.x, this->y -= rhs.y;
    return *this;
  }
  Point operator-(const Point& rhs) const { return Point(*this) -= rhs; }
  double atan2() const { return ::atan2(y, x); }
};

const double pi = acos(-1.0);

int main() {
  int N;
  cin >> N;
  vector<Point> vp(N);
  repeat(i, N) cin >> vp[i].x >> vp[i].y;

  double ans = 0.0;
  repeat(i, N) {
    vector<double> ang;
    ang.reserve(N - 1);
    repeat(j, N) if (j != i)
        ang.push_back((vp[j] - vp[i]).atan2() * 180.0 / pi);

    sort(ang.begin(), ang.end());

    repeat(j, N - 1) {
      double base = ang[j] + 180.0;
      if (base >= 360.0)
        base -= 360.0;

      int k = lower_bound(ang.begin(), ang.end(), base) - ang.begin();

      if (k == N - 1)
        k -= N - 1;

      double angle = min(abs(ang[k] - ang[j]), 360.0 - abs(ang[k] - ang[j]));
      ans = max(ans, angle);

      k = (k - 1 + N - 1) % (N - 1);
      angle = min(abs(ang[k] - ang[j]), 360.0 - abs(ang[k] - ang[j]));
      ans = max(ans, angle);
    }
  }

  cout << fixed << setprecision(10) << ans << endl;

  return 0;
}