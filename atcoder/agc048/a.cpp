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
  int q{0};
  cin >> q;
  const string atcoder = "atcoder";
  while (q--) {
    string s;
    cin >> s;
    if (s > atcoder) {
      cout << 0 << endl;
      continue;
    }
    int k = 0;
    const int len = s.size();
    while (k < len and s[k] == 'a') ++k;
    if (k == len) {
      cout << -1 << endl;
      continue;
    }
    if (s[k] > 't') {
      cout << k - 1 << endl;
    } else {
      cout << k << endl;
    }
  }
  return 0;
}