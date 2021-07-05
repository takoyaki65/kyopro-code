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

using ll = long long;
ll px[100005], py[100005];
int N, Q;

int main() {
  cin >> N >> Q;
  repeat(i, N) {
    ll x, y;
    cin >> x >> y;
    px[i] = x - y;
    py[i] = x + y;
  }

  ll xmin = numeric_limits<ll>::max();
  ll xmax = numeric_limits<ll>::min();
  ll ymin = numeric_limits<ll>::max();
  ll ymax = numeric_limits<ll>::min();

  repeat(i, N) {
    xmin = min(xmin, px[i]);
    xmax = max(xmax, px[i]);
    ymin = min(ymin, py[i]);
    ymax = max(ymax, py[i]);
  }

  while (Q--) {
    int q;
    cin >> q;
    --q;
    cout << max({px[q] - xmin, xmax - px[q], py[q] - ymin, ymax - py[q]})
         << endl;
  }
  return 0;
}