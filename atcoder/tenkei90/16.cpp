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

int main() {
  long long n, a, b, c;
  cin >> n >> a >> b >> c;
  vector<long long> v = {a, b, c};
  sort(v.rbegin(), v.rend());
  a = v[0], b = v[1], c = v[2];

  long long ans = 100000;
  for (long long i = 0, cur1 = 0; i <= 9999 && cur1 <= n; ++i, cur1 += a) {
    for (long long j = 0, cur2 = cur1; j <= 9999 && cur2 <= n; ++j, cur2 += b) {
      long long remain = n - cur2;
      if (remain >= 0 && remain % c == 0)
        setmin(ans, i + j + remain / c);
    }
  }

  cout << ans << endl;

  return 0;
}