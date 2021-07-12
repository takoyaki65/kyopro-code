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
#include <random>
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

int N;
int L[2002], R[2002];

int main() {
  cin >> N;
  repeat(i, N) {
    int t, l, r;
    cin >> t >> l >> r;
    l *= 2, r *= 2;
    if (t == 1)
      /* do nothing */;
    else if (t == 2)
      r -= 1;
    else if (t == 3)
      l += 1;
    else
      l += 1, r -= 1;
    L[i] = l, R[i] = r;
  }

  // repeat(i, N) { cout << L[i] << ", " << R[i] << endl; }

  int ans = 0;
  repeat(i, N) {
    repeat_from(j, i + 1, N) {
      if (L[i] > R[j] || R[i] < L[j])
        /* do nothing */;
      else
        ans += 1;
    }
  }
  cout << ans << endl;
  return 0;
}