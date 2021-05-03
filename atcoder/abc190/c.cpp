#include <algorithm>
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

const int MAX_N = 110;
int dish[MAX_N];

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> va(m), vb(m);
  repeat(i, m) {
    cin >> va[i] >> vb[i];
    --va[i], --vb[i];
  }
  int k;
  cin >> k;
  vector<int> vc(k), vd(k);
  repeat(i, k) {
    cin >> vc[i] >> vd[i];
    --vc[i], --vd[i];
  }

  int ans = 0;
  repeat(bit, 1 << k) {
    memset(dish, 0, sizeof(dish));

    for (int i = 0; i < k; ++i) {
      if (bit & (1 << i))
        dish[vc[i]]++;
      else
        dish[vd[i]]++;
    }

    int tmp = 0;
    for (int i = 0; i < m; ++i) {
      if (dish[va[i]] && dish[vb[i]])
        ++tmp;
    }
    setmax(ans, tmp);
    }
  cout << ans << endl;
  return 0;
}