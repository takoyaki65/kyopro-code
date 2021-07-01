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

struct task {
  int d, c;
  long long s;
  bool operator<(const task& rhs) const { return d < rhs.d; }
};

int N;
long long dp1[5001], dp2[5001];
task vtask[5001];

int main() {
  cin >> N;
  repeat(i, N) cin >> vtask[i].d >> vtask[i].c >> vtask[i].s;
  sort(vtask, vtask + N);

  long long *prev = dp1, *next = dp2;
  repeat(i, N) {
    auto [d, c, s] = vtask[i];
    // repeat(j, 5001) {
    //   if (c <= j && j <= d) {
    //     next[j] = max(prev[j], prev[j - c] + s);
    //   } else {
    //     next[j] = prev[j];
    //   }
    // }
    for (int j = 0; j < c; j++) {
      next[j] = prev[j];
    }
    for (int j = c; j <= d; j++) {
      next[j] = max(prev[j], prev[j - c] + s);
    }
    for (int j = d + 1; j < 5001; j++) {
      next[j] = prev[j];
    }

    swap(prev, next);
  }

  cout << *max_element(prev, prev + 5001) << endl;
  return 0;
}