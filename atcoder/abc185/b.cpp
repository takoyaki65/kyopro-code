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

int main() {
  int n{0}, m{0}, t{0};
  cin >> n >> m >> t;
  int bp{0};
  int vol{n};
  bool flg = true;
  while(m--) {
    int a{0}, b{0};
    cin >> a >> b;
    vol -= (a - bp);
    if(vol <= 0) {
      flg = false;
    }
    vol += (b - a);
    if(vol > n) vol = n;
    bp = b;
  }
  vol -= (t - bp);
  if(vol <= 0) flg = false;
  cout << (flg ? "Yes" : "No") << endl;
  return 0;
}