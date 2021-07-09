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
#include <random>
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

using Vertex_type = vector<int>;
using Graph_type = vector<Vertex_type>;

struct scc_graph {
  int n;
  int scc_num;
  int dag_num;
  Graph_type G;
  Graph_type rG;
  vector<int> group;
  vector<vector<int>> vGroup;
  vector<bool> visited;
  // dag_id[v] = id : 頂点vはid番目のDAG上にある
  vector<int> dag_id;

  scc_graph(int _n)
      : n(_n),
        scc_num(0),
        dag_num(0),
        G(_n, Vertex_type()),
        rG(_n, Vertex_type()),
        group(_n, 0),
        vGroup(_n, vector<int>()),
        visited(_n, false),
        dag_id(_n, -1) {}

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

  void dag_dfs(int cur, int id) {
    dag_id[cur] = id;
    for (const int& to : G[cur]) {
      if (dag_id[to] == -1) {
        dag_dfs(to, id);
      }
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
    scc_num = id;

    fill(dag_id.begin(), dag_id.end(), -1);
    int dag_num = 0;
    for (int i = 0; i < scc_num; ++i) {
      int v = vGroup[i][0];
      if (dag_id[v] == -1)
        dag_dfs(v, dag_num++);
    }
  }
};

/**
 * WA解法
 * 例えば、
 *
10 11 10
6 10
5 10
6 8
1 7
5 9
2 3
4 5
1 2
6 7
5 8
6 9
8 9
7 10
5 9
4 10
6 7
3 6
7 10
6 7
8 9
3 7

Correct Answer
No
No
Yes
Yes
Yes
No
No
Yes
No
No

Wrong Answer
Yes
No
No
No
Yes
No
No
Yes
Yes
No
 *
 */

int main() {
  int N, M, Q;
  cin >> N >> M >> Q;
  scc_graph scc(N);
  repeat(i, M) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    scc.addEdge(x, y);
  }

  scc.construct();

  while (Q--) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    // この条件を満たすからといって、aからbに到達可能とは限らない
    if (scc.dag_id[a] == scc.dag_id[b] && scc.group[a] <= scc.group[b]) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }

  return 0;
}