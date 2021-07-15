// https://ei1333.hateblo.jp/entry/2017/04/10/224413
// 全方位木DPで解く
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

const int INF = 1 << 30;

struct edge {
  int to, cost, type;
};

vector<edge> g[100000];
int N, D, dist[100000];
int weight[100000];

void dfs1(int idx, int par) {
  for (const edge& e : g[idx]) {
    if (e.to == par)
      continue;
    dfs1(e.to, idx);
    dist[idx] = max(dist[idx], dist[e.to] + e.cost);
    weight[idx] += weight[e.to] + e.type;
  }
}

int dfs2(int idx, int d_par, int d_weight, int par) {
  vector<pair<int, int>> d_child;

  int latte = 0;
  d_child.emplace_back(0, -1);  // 番兵
  for (const edge& e : g[idx]) {
    if (e.to == par) {
      d_child.emplace_back(d_par + e.cost, e.to);
      latte += d_weight + e.type;
    } else {
      d_child.emplace_back(dist[e.to] + e.cost, e.to);
      latte += e.type + weight[e.to];
    }
  }
  sort(d_child.rbegin(), d_child.rend());

  int ret = INF;
  if (d_child[0].first <= D) {
    ret = min(ret, latte);
  }
  for (const edge& e : g[idx]) {
    if (e.to == par)
      continue;
    ret = min(ret, dfs2(e.to, d_child[d_child[0].second == e.to].first,
                        latte - weight[e.to] - e.type, idx));
  }
  return ret;
}

int main() {
  cin >> N >> D;
  repeat(i, N - 1) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    g[a].push_back(edge{b, c, 1});
    g[b].push_back(edge{a, c, 0});
  }

  dfs1(0, -1);
  int get = dfs2(0, 0, 0, -1);
  if (get == INF)
    cout << -1 << endl;
  else
    cout << get << endl;
  return 0;
}