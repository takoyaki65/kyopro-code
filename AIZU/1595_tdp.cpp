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
vector<int> g[100000];
int dist[100000], ans[100000];

void dfs1(int idx, int par) {
  for (const int& to : g[idx]) {
    if (to == par)
      continue;
    dfs1(to, idx);
    dist[idx] = max(dist[idx], dist[to] + 1);
  }
}

void dfs2(int idx, int d_par, int par) {
  vector<pair<int, int>> d_child;
  d_child.emplace_back(0, -1);
  for (const int& to : g[idx]) {
    if (to == par)
      d_child.emplace_back(d_par + 1, to);
    else
      d_child.emplace_back(dist[to] + 1, to);
  }
  sort(d_child.rbegin(), d_child.rend());
  ans[idx] = d_child[0].first;
  for (const int& to : g[idx]) {
    if (to == par)
      continue;
    dfs2(to, d_child[d_child[0].second == to].first, idx);
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

  // dfs1で頂点0を根として、各頂点vから葉までの最長距離を求め
  dfs1(0, -1);
  // dfs2で各頂点を根としたときの、葉までの最長距離を求める
  dfs2(0, 0, -1);

  repeat(i, N) { cout << (N - 1) * 2 - ans[i] << endl; }
}