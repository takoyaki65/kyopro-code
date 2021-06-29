#include <algorithm>
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

typedef long long ll;
const ll maxL = numeric_limits<ll>::max();

ll mySqrt(ll x) {
  if (x == 0)
    return 0;
  assert(x >= 0);
  ll l = 0, r = 3037000499LL;
  while (abs(r - l) > 1) {
    ll mid = (l + r) / 2;
    if (mid * mid <= x)
      l = mid;
    else
      r = mid;
  }
  return l;
}

ll calcLatticePoints(ll left, ll right, ll div) {
  left += 1000100000;
  right += 1000100000;
  if (left % div == 0) {
    --left;
  }
  return right / div - left / div;
}

int main() {
  long double X, Y, R;
  cin >> X >> Y >> R;
  ll x = round(X * 10000), y = round(Y * 10000), r = round(R * 10000);

  // cout << X << " -> " << x << endl;
  // cout << Y << " -> " << y << endl;
  // cout << R << " -> " << r << endl;

  x %= 10000;
  y %= 10000;
  ll ans = 0;
  for (ll dy = 0; dy <= 1000000000LL + 100000LL; dy += 10000LL) {
    ll py = dy;
    if (abs(y - py) <= r) {
      ll cut = mySqrt(r * r - (y - py) * (y - py));
      ans += calcLatticePoints(x - cut, x + cut, 10000);
    }
    if (dy > 0) {
      py = -dy;
      if (abs(y - py) <= r) {
        ll cut = mySqrt(r * r - (y - py) * (y - py));
        ans += calcLatticePoints(x - cut, x + cut, 10000);
      }
    }
  }

  cout << ans << endl;
  return 0;
}