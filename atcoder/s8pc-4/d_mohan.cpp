#include <algorithm>
#include <array>
#include <bitset>
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
#define bit_stand(n, k) ((n >> k) & 1)
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
vector<int> g[150001];
double dp1[150001], dp2[150001];

void rec1(int v, int par) {
  double val = 0.0;
  int p = g[v].size();
  if (par != -1)
    p -= 1;
  for (const int& to : g[v]) {
    if (to == par)
      continue;
    rec1(to, v);
    val += (1.0 + dp1[to]) * (1.0 / p);
  }
  dp1[v] = val;
}

void rec2(int v, int par) {
  double val = (par == -1) ? 0 : 1;
  if (par != -1) {
    int p = g[par].size();
    if (p > 1) {
      // 親の次数が1より大きい場合
      if (par != 0) {
        // 親が根でない場合
        val += dp2[par] / (p - 1);
        val += (dp1[par] * (p - 1) - (1 + dp1[v])) / (p - 1);
      } else {
        // 親が根の場合
        val += (dp1[par] * p - (1 + dp1[v])) / (p - 1);
      }
    } else {
      // 親の次数が1の場合
      // do nothing
    }
  }
  dp2[v] = val;

  for (const int& to : g[v]) {
    if (to != par) {
      rec2(to, v);
    }
  }
}

int main() {
  cin >> N;
  repeat(i, N - 1) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  rec1(0, -1);
  // cout << "dp1: " << endl;
  // for (int i = 0; i < N; ++i) {
  //   cout << i + 1 << " " << dp1[i] << endl;
  // }
  rec2(0, -1);
  // cout << "dp2: " << endl;
  // for (int i = 0; i < N; ++i) {
  //   cout << i + 1 << " " << dp2[i] << endl;
  // }

  for (int i = 0; i < N; ++i) {
    int p = g[i].size();
    double ans = 0.0;
    if (i == 0)
      ans = dp1[i];
    else
      ans = (dp1[i] * (p - 1) + dp2[i]) / p;
    cout << fixed << setprecision(10) << ans << endl;
  }

  return 0;
}