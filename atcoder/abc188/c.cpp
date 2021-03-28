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

int main() {
  int n;
  cin >> n;
  const int num = 1 << n;
  std::vector<int> a(num);
  repeat(i, num) cin >> a[i];

  // [left, right)
  auto battle = [&](auto f, int left, int right) -> int {
    if (right - left == 1) {
      return left;
    }
    int one = f(f, left, left + (right - left) / 2);
    int other = f(f, left + (right - left) / 2, right);
    if (a[one] < a[other])
      return other;
    else
      return one;
  };

  int one = battle(battle, 0, num / 2);
  int other = battle(battle, num / 2, num);
  if (a[one] < a[other])
    std::cout << one + 1 << std::endl;
  else
    std::cout << other + 1 << std::endl;
  return 0;
}