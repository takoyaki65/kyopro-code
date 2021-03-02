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
inline int sz(T &x) {
  return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T &a, T b) {
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

// 0-indexedに直して考える
// 頂点0を根とする
// t = 1のとき(a_ei -> b_ei)
// a_eiが親，b_eiが子の場合，根(0)に+x_i，b_eiに-x_i加える
// a_eiが子，b_eiが親の場合，a_eiに+x_i加える
// 最後に根から葉に向かって累積和をとる

void tree_order(const vector<vector<int>> &graph, vector<int> &depth, int cur,
                int ord) {
  depth[cur] = ord;
  for (int to : graph[cur]) {
    if (depth[to] == -1) {
      tree_order(graph, depth, to, ord + 1);
    }
  }
}

void sum_dfs(const vector<vector<int>> &graph, const vector<int> &depth,
             vector<long long> &ans, int cur) {
  for (int to : graph[cur]) {
    if (depth[cur] < depth[to]) {
      ans[to] += ans[cur];
      sum_dfs(graph, depth, ans, to);
    }
  }
}

int main() {
  int n;
  cin >> n;

  auto graph = vectors(0, n, 0);
  vector<int> a(n - 1), b(n - 1);
  repeat(i, n - 1) {
    cin >> a[i] >> b[i];
    --a[i], --b[i];
    graph[a[i]].push_back(b[i]);
    graph[b[i]].push_back(a[i]);
  }

  vector<int> depth(n, -1);
  tree_order(graph, depth, 0, 0);

  vector<long long> ans(n, 0);
  int q;
  cin >> q;
  while (q--) {
    int t, e, x;
    cin >> t >> e >> x;
    --e;

    int ae = a[e], be = b[e];
    if (t == 2) swap(ae, be);
    // ae から beをたどらないで行ける全部の頂点に+x
    if (depth[ae] < depth[be]) {
      ans[0] += x;
      ans[be] -= x;
    } else {
      if (depth[ae] == depth[be]) {
        cerr << "error!" << endl;
        return 0;
      }
      ans[ae] += x;
    }
  }

  sum_dfs(graph, depth, ans, 0);
  repeat(i, n) cout << ans[i] << endl;

  return 0;
}