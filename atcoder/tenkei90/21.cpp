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

using Vertex_type = vector<int>;
using Graph_type = vector<Vertex_type>;

struct scc_graph {
  int n;
  Graph_type G;
  Graph_type rG;
  vector<int> group;
  vector<vector<int>> vGroup;
  vector<bool> visited;

  scc_graph(int _n)
      : n(_n),
        G(_n, Vertex_type()),
        rG(_n, Vertex_type()),
        group(_n, 0),
        vGroup(_n, vector<int>()),
        visited(_n, false) {}

  void addEdge(int from, int to) {
    G[from].push_back(to);
    rG[to].push_back(from);
  }

  void dfs(int cur, vector<int>& stk) {
    visited[cur] = true;
    for (const int& to : G[cur]) {
      if (!visited[to])
        dfs(to, stk);
    }
    stk.push_back(cur);
  }

  void rdfs(int cur, int id) {
    group[cur] = id;
    visited[cur] = true;
    vGroup[id].push_back(cur);
    for (const int& to : rG[cur]) {
      if (!visited[to])
        rdfs(to, id);
    }
  }

  void construct() {
    fill(visited.begin(), visited.end(), false);
    vector<int> stk;
    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        dfs(i, stk);
      }
    }
    assert(stk.size() == n);

    fill(visited.begin(), visited.end(), false);
    int id = 0;
    for (int i = n - 1; i >= 0; --i) {
      int v = stk[i];
      if (!visited[v]) {
        rdfs(v, id++);
      }
    }
  }
};

int main() {
  int N, M;
  cin >> N >> M;

  scc_graph scc(N);
  repeat(i, M) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    scc.addEdge(a, b);
  }

  scc.construct();

  const auto& vGroup = scc.vGroup;
  long long ans = 0;
  for (const auto& group : vGroup) {
    long long group_size = group.size();
    ans += group_size * (group_size - 1) / 2;
  }

  cout << ans << endl;

  return 0;
}