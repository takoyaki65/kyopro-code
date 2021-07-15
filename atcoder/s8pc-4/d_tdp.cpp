// https://ei1333.hateblo.jp/entry/2017/04/10/224413
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
vector<int> g[150000];
double ee[150000], ans[150000];

void dfs1(int idx, int par) {
  double ret = 0;
  int child = 0;

  for (const int& to : g[idx]) {
    if (to == par)
      continue;
    dfs1(to, idx);
    ret += ee[to] + 1.0;
    child += 1;
  }
  ee[idx] = 0;
  if (child >= 1)
    ee[idx] += ret / child;
}

void dfs2(int idx, double d_par, int par) {
  double ret = 0;
  for (const int& to : g[idx]) {
    if (to == par)
      ret += d_par + 1.0;
    else
      ret += ee[to] + 1.0;
  }
  ans[idx] = ret / g[idx].size();
  for (const int& to : g[idx]) {
    if (to == par)
      continue;
    dfs2(to, (ret - ee[to] - 1.0) / max(1, (int)g[idx].size() - 1), idx);
  }
}

int main() {
  cin >> N;
  repeat(i, N - 1) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  dfs1(0, -1);
  dfs2(0, 0, -1);
  for (int i = 0; i < N; ++i)
    cout << fixed << setprecision(10) << ans[i] << endl;
  return 0;
}