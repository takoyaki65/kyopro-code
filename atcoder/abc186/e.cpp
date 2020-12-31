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

void extgcd(long long a, long long b, long long& x, long long& y) {
  if (b != 0) {
    extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  } else {
    x = 1, y = 0;
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    long long n, s, k;
    cin >> n >> s >> k;
    long long d = __gcd(n, __gcd(s, k));
    n /= d, s /= d, k /= d;
    s *= -1;
    while (s < 0) s += n;
    if (__gcd(k, n) != 1) {
      cout << -1 << endl;
    } else {
      long long inv = 1, y = 0;
      extgcd(k, n, inv, y);
      while (inv < 0) inv += n;
      long long ans = inv * s % n;
      cout << ans << endl;
    }
  }
  return 0;
}