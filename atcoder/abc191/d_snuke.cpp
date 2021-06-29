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

// atcoder放送解
// https://www.youtube.com/watch?v=iEfDi7wagfE

using ll = long long;
int in() {
  double x;
  cin >> x;
  x *= 10000;
  return round(x);
}

bool ok(ll dx, ll dy, ll z) {
  return dx * dx + dy * dy <= z * z;
}

ll f(ll x, ll y, ll z, ll lim) {
  int l = 0, r = 1;
  ll res = 0;
  for (int i = int(1e9) + 50000; i >= lim; i -= 10000) {
    while (ok(x - l * 10000, i - y, z))
      --l;
    while (ok(r * 10000 - x, i - y, z))
      ++r;
    res += r - l - 1;
  }
  return res;
}

int main() {
  ll x = in();
  ll y = in();
  ll z = in();
  x %= 10000;
  y %= 10000;
  ll ans = f(x, y, z, 10000);
  ans += f(x, -y, z, 0);
  cout << ans << endl;
  return 0;
}