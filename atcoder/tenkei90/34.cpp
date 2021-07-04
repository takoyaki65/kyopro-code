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

int main() {
  int N, K;
  cin >> N >> K;
  vector<int> a(N);
  repeat(i, N) cin >> a[i];

  // [l, r)
  int l = 0, r = 0, num = 0;
  int ans = 0;
  map<int, int> Map;

  for (r = 1; r <= N; ++r) {
    auto itr = Map.find(a[r - 1]);
    if (itr != Map.end()) {
      itr->second += 1;
    } else {
      Map[a[r - 1]] = 1;
      num += 1;
    }

    while (num > K && l < N) {
      itr = Map.find(a[l]);
      itr->second -= 1;
      if (itr->second == 0) {
        Map.erase(itr);
        --num;
      }
      ++l;
    }

    ans = max(ans, r - l);
  }
  cout << ans << endl;
  return 0;
}