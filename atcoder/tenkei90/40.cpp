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

const int INF = 1000000000;

struct flow_graph {
  struct edge {
    int to, cap, rev;
  };

  int size;
  vector<vector<edge>> G;
  vector<bool> used;

  flow_graph(int _size) : size(_size) {
    G.assign(size, vector<edge>());
    used.assign(size, false);
  }

  void add_edge(int from, int to, int cap) {
    edge F;
    edge T;
    F.to = to;
    F.cap = cap;
    F.rev = G[to].size();
    G[from].push_back(F);

    T.to = from;
    T.cap = 0;
    T.rev = G[from].size() - 1;
    G[to].push_back(T);
  }

  // 増加パスをDFSで探す
  int dfs(int v, int t, int f) {
    if (v == t)
      return f;
    used[v] = true;
    for (int i = 0; i < G[v].size(); ++i) {
      edge& e = G[v][i];
      if (!used[e.to] && e.cap > 0) {
        int d = dfs(e.to, t, min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  // sからtまでの最大流を求める
  int max_flow(int s, int t) {
    int flow = 0;
    while (true) {
      fill(used.begin(), used.end(), false);
      int f = dfs(s, t, INF);
      if (f == 0)
        return flow;
      flow += f;
    }
    return flow;
  }
};

int main() {
  int N, W;
  cin >> N >> W;
  vector<int> a(N + 1);
  flow_graph flGraph(N + 2);
  for (int i = 1; i <= N; ++i)
    flGraph.add_edge(0, i, W);
  for (int i = 1; i <= N; ++i) {
    cin >> a[i];
    flGraph.add_edge(i, N + 1, a[i]);
  }
  for (int i = 1; i <= N; ++i) {
    int k;
    cin >> k;
    repeat(j, k) {
      int cij;
      cin >> cij;
      flGraph.add_edge(i, cij, numeric_limits<int>::max());
    }
  }

  int max_flow = flGraph.max_flow(0, N + 1);
  // cout << "max_flow: " << max_flow << endl;
  // for (int i = 0; i < N + 2; ++i) {
  //   for (auto [to, cap, rev] : flGraph.G[i]) {
  //     cout << i << " -> " << to << " : " << cap << endl;
  //   }
  // }
  int ans = 0;
  for (int i = 1; i <= N; ++i)
    ans += a[i];
  ans -= max_flow;
  cout << ans << endl;

  return 0;
}