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

bool check10(int x) {
  if (x == 0) return true;
  if (x % 10 == 7) return false;
  return check10(x / 10);
}

bool check8(int x) {
  if (x == 0) return true;
  if (x % 8 == 7) return false;
  return check8(x / 8);
}

int main() {
  int n;
  cin >> n;
  int ans = 0;
  for (int x = 1; x <= n; ++x) {
    if (!check10(x)) continue;
    if (!check8(x)) continue;
    ++ans;
  }
  cout << ans << endl;
  return 0;
}