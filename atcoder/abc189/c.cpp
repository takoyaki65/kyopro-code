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

const int max_n = 10010;
long long a[max_n];
int n;

int main() {
  cin >> n;
  repeat(i, n) cin >> a[i];

  long long ans = 0;
  for (int l = 0; l < n; ++l) {
    long long sum = a[l];
    long long min_val = a[l];
    for (int r = l; r < n; ++r) {
      setmin(min_val, a[r]);
      setmax(sum, min_val * (r - l + 1));
    }
    setmax(ans, sum);
  }
  cout << ans << endl;
  return 0;
}