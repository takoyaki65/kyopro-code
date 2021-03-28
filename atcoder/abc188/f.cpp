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

std::map<long long, long long> ans;

long long rec(long long x, long long y) {
  auto itr = ans.find(y);
  if (itr != ans.end()) {
    return itr->second;
  }

  long long ret;
  if (y == 1) {
    ret = abs(x - y);
  } else if (y % 2 == 0) {
    ret = min(abs(x - y), rec(x, y / 2) + 1);
  } else {
    ret = min(abs(x - y), rec(x, (y + 1) / 2) + 2);
    ret = min(ret, rec(x, (y - 1) / 2) + 2);
  }
  ans[y] = ret;
  return ret;
}

int main() {
  long long x, y;
  cin >> x >> y;
  std::cout << rec(x, y) << std::endl;
  return 0;
}