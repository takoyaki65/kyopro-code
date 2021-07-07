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
#include <unordered_map>
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

struct swVector {
  vector<int> dat;
  int n;
  int shift_val;
  swVector(int n_, vector<int> dat_) : n(n_), dat(dat_), shift_val(0) {}

  int& operator[](int idx) { return dat[(idx - shift_val + n) % n]; }
  int operator[](int idx) const { return dat[(idx - shift_val + n) % n]; }
  void shift() {
    shift_val += 1;
    if (shift_val >= n)
      shift_val = 0;
  }
};

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> va(N);
  repeat(i, N) cin >> va[i];
  swVector swv(N, va);
  while (Q--) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1) {
      --x, --y;
      swap(swv[x], swv[y]);
    } else if (t == 2) {
      swv.shift();
    } else {
      --x;
      cout << swv[x] << endl;
    }
  }
  return 0;
}