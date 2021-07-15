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

struct edge {
  int to, cost;
};

int N;
vector<edge> g[100000];
long long dist[100000];

void dfs1(int idx, int par) {
  for (const edge& e : g[idx]) {
    if (e.to == par)
      continue;
    dfs1(e.to, idx);
    dist[idx] = max(dist[idx], dist[e.to] + e.cost);
  }
}

int dfs2(int idx, int d_par, int par) {
  // d_child[i] := {dist, v} 頂点idxから、頂点vを含む部分木への最大距離
  vector<pair<int, int>> d_child;
  d_child.emplace_back(0, -1);  // 番兵
  for (const edge& e : g[idx]) {
    if (e.to == par)
      d_child.emplace_back(d_par + e.cost, e.to);
    else
      d_child.emplace_back(e.cost + dist[e.to], e.to);
  }
  sort(d_child.rbegin(), d_child.rend());
  int ret = d_child[0].first + d_child[1].first;
  for (const edge& e : g[idx]) {
    if (e.to == par)
      continue;
    // 基本はd_child()の最大がd_parになるが、
    // e.toの部分木が最大値のときはそれを
    // 取り除く必要がある
    ret = max(ret, dfs2(e.to, d_child[d_child[0].second == e.to].first, idx));
  }
  return ret;
}

int main() {
  cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int a, b, w;
    cin >> a >> b >> w;
    g[a].push_back(edge{b, w});
    g[b].push_back(edge{a, w});
  }

  dfs1(N / 2, -1);
  cout << dfs2(N / 2, 0, -1) << endl;

  return 0;
}