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
inline int sz(T &x) {
  return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T &a, T b) {
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

using ll = long long;

int main() {
  int n{0};
  ll c{0}, k{0};
  cin >> n >> c >> k;
  vector<ll> t(n);
  repeat(i, n) cin >> t[i];
  sort(t.begin(), t.end());
  int cur = 0;
  int res = 0;
  while (cur < n) {
    int capa = 1;
    int dept = t[cur] + k;
    ++res;
    ++cur;
    while (cur < n and capa < c and t[cur] <= dept) {
      ++capa;
      ++cur;
    }
  }
  cout << res << endl;
  return 0;
}