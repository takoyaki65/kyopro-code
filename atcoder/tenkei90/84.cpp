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

int main() {
  int N;
  string S;
  cin >> N >> S;
  int r = 0;
  int maru = 0, batsu = 0;
  //[l,r)
  long long ans = 0;
  for (int l = 0; l < N; ++l) {
    while (r < N && (maru == 0 || batsu == 0)) {
      if (S[r] == 'o')
        maru += 1;
      else
        batsu += 1;
      r += 1;
    }
    if (maru && batsu) {
      // cout << "l: " << l << "r: " << r << endl;
      ans += N - r + 1;
    }
    if (S[l] == 'o')
      maru -= 1;
    else
      batsu -= 1;
  }
  cout << ans << endl;
  return 0;
}