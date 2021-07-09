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

std::random_device rnd;
std::mt19937 mt(rnd());

std::uniform_int_distribution<> rand2_10(2, 10);
std::uniform_int_distribution<> rand1_60(1, 60);
std::uniform_int_distribution<> rand1_20(1, 20);
std::uniform_int_distribution<> rand1_70(1, 70);

struct Testcase {
  int N, M, Q;
  vector<int> X, Y, A, B;
  friend ostream& operator<<(ostream& os, const Testcase& rhs) {
    os << rhs.N << " " << rhs.M << " " << rhs.Q << endl;
    repeat(i, rhs.M) { os << rhs.X[i] << " " << rhs.Y[i] << endl; }
    repeat(i, rhs.Q) { os << rhs.A[i] << " " << rhs.B[i] << endl; }
    return os;
  }
};

Testcase GenTestcase() {
  Testcase ret;
  ret.N = rand2_10(mt);
  ret.M = rand1_20(mt);
  ret.Q = rand1_70(mt);
  ret.X.assign(ret.M, 0);
  ret.Y.assign(ret.M, 0);
  ret.A.assign(ret.Q, 0);
  ret.B.assign(ret.Q, 0);
  std::uniform_int_distribution<> rand1_N(1, ret.N);
  repeat(i, ret.M) {
    while (ret.X[i] == ret.Y[i]) {
      ret.X[i] = rand1_N(mt), ret.Y[i] = rand1_N(mt);
    }
    if (ret.X[i] > ret.Y[i])
      swap(ret.X[i], ret.Y[i]);
  }
  repeat(i, ret.Q) {
    while (ret.A[i] == ret.B[i]) {
      ret.A[i] = rand1_N(mt), ret.B[i] = rand1_N(mt);
    }
    if (ret.A[i] > ret.B[i])
      swap(ret.A[i], ret.B[i]);
  }
  return ret;
}

struct Answer {
  vector<int> q;
  Answer(int size) : q(size, 0) {}
  bool operator==(const Answer& rhs) const { return q == rhs.q; }
  bool operator!=(const Answer& rhs) const { return q != rhs.q; }
  friend ostream& operator<<(ostream& os, const Answer& rhs) {
    for (const int& v : rhs.q) {
      if (v == 0)
        os << "No" << endl;
      else
        os << "Yes" << endl;
    }
    return os;
  }
};

using Vertex_type = vector<int>;
using Graph_type = vector<Vertex_type>;

void rec(int v, const Graph_type& G, vector<bool>& visit) {
  visit[v] = true;
  for (const int& to : G[v]) {
    if (visit[to] == false) {
      rec(to, G, visit);
    }
  }
}

Answer Solver_guchoku(const Testcase& tc) {
  const int N = tc.N, M = tc.M, Q = tc.Q;
  const auto &X = tc.X, &Y = tc.Y, &A = tc.A, &B = tc.B;

  Graph_type G(N);
  repeat(i, M) { G[X[i] - 1].push_back(Y[i] - 1); }

  vector<bool> visit(N);
  Answer ret(Q);

  repeat(i, Q) {
    int a = A[i] - 1, b = B[i] - 1;
    fill(visit.begin(), visit.end(), false);
    rec(a, G, visit);
    if (visit[b] == true) {
      ret.q[i] = 1;
    } else {
      ret.q[i] = 0;
    }
  }

  return ret;
}

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

Answer Solver_submit(const Testcase& tc) {
  const int N = tc.N, M = tc.M, Q = tc.Q;
  const auto &X = tc.X, &Y = tc.Y, &A = tc.A, &B = tc.B;
  scc_graph scc(N);
  repeat(i, M) { scc.addEdge(X[i] - 1, Y[i] - 1); }
  scc.construct();

  Answer ret(Q);
  repeat(i, Q) {
    int a = A[i] - 1, b = B[i] - 1;
    if (scc.dag_id[a] == scc.dag_id[b] && scc.group[a] <= scc.group[b]) {
      // cout << "Yes" << endl;
      ret.q[i] = 1;
    } else {
      // cout << "No" << endl;
      ret.q[i] = 0;
    }
  }
  return ret;
}

int main() {
  int case_num = 100;
  while (case_num--) {
    auto tc = GenTestcase();
    auto ans_guchoku = Solver_guchoku(tc);
    auto ans_submit = Solver_submit(tc);
    if (ans_guchoku != ans_submit) {
      cout << "Wrong Answer generated!" << endl;
      cout << "test case: " << endl;
      cout << tc << endl;
      cout << "Correct Answer" << endl;
      cout << ans_guchoku << endl;
      cout << "Wrong Answer" << endl;
      cout << ans_submit << endl;
    }
  }
  return 0;
}