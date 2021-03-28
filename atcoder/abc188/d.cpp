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

struct plan {
  // (data)日に支払い量が(add)円増える予定
  int date, add;
};

struct less_date {
  bool operator()(const plan& lhs, const plan& rhs) {
    return lhs.date < rhs.date;
  }
};

int main() {
  int n;
  long long c;
  cin >> n >> c;
  std::vector<int> va(n), vb(n), vc(n);
  repeat(i, n) cin >> va[i] >> vb[i] >> vc[i];

  std::vector<plan> vplan(2 * n);
  repeat(i, n) {
    vplan[2 * i].date = va[i];
    vplan[2 * i].add = +vc[i];
    vplan[2 * i + 1].date = vb[i] + 1;
    vplan[2 * i + 1].add = -vc[i];
  }

  std::sort(vplan.begin(), vplan.end(), less_date());

  long long ans = 0;
  long long payment = 0;
  for (int i = 0; i < 2 * n - 1; ++i) {
    payment += vplan[i].add;
    long long term = vplan[i + 1].date - vplan[i].date;
    ans += term * min(payment, c);
  }
  std::cout << ans << std::endl;
  return 0;
}