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
// ev[v] := 頂点0を根とし、
//          各頂点vから、その部分木へ移動する時の
//          操作回数の期待値
double ev[150001];

double ans[150001];

void rec1(int v, int par) {
  double val = 0.0;
  int p = g[v].size();
  if (par != -1)
    p -= 1;
  for (const int& to : g[v]) {
    if (to == par)
      continue;
    rec1(to, v);
    val += (1.0 + ev[to]) * (1.0 / p);
  }
  ev[v] = val;
}

void rec2(int v, double d_par, int par) {
  // cout << "v: " << v << " d_par: " << d_par << " par: " << par << endl;
  double val1 = 0.0;
  int p = g[v].size();
  for (const int& to : g[v]) {
    if (to == par) {
      val1 += (1.0 + d_par) * (1.0 / p);
    } else {
      val1 += (1.0 + ev[to]) * (1.0 / p);
    }
  }

  // cout << "val1: " << val1 << endl;

  ans[v] = val1;

  double val2 = 0.0;
  if (p > 1) {
    for (const int& to : g[v]) {
      if (to == par) {
        val2 += (1.0 + d_par) * (1.0 / (p - 1));
      } else {
        val2 += (1.0 + ev[to]) * (1.0 / (p - 1));
      }
    }
  }

  // cout << "val2: " << val2 << endl;

  for (const int& to : g[v]) {
    if (to != par) {
      double next_d_par = val2;
      if (p > 1)
        next_d_par -= (1.0 + ev[to]) * (1.0 / (p - 1));
      // cout << "next_d_par: " << next_d_par << endl;
      rec2(to, next_d_par, v);
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
  // cout << "ev:  " << endl;
  // repeat(i, N) cout << i + 1 << " : " << ev[i] << endl;
  // cout << endl;
  rec2(0, 0, -1);
  for (int i = 0; i < N; ++i) {
    cout << fixed << setprecision(10) << ans[i] << endl;
  }

  return 0;
}