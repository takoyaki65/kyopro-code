#include <algorithm>
#include <array>
#include <atcoder/maxflow>
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

int N, T;
int ax[20050], ay[20050], bx[20050], by[20050];
const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {
  cin >> N >> T;
  repeat(i, N) cin >> ax[i] >> ay[i];
  repeat(i, N) cin >> bx[i] >> by[i];

  map<pair<int, int>, int> dir;
  repeat(i, 8) dir[{dx[i], dy[i]}] = i;

  map<pair<int, int>, vector<int>> dict;
  repeat(i, N) {
    repeat(k, 8) {
      int nx = ax[i] + T * dx[k], ny = ay[i] + T * dy[k];
      dict[{nx, ny}].push_back(i);
    }
  }

  // souce , tank
  const int s = 2 * N, t = 2 * N + 1;
  atcoder::mf_graph<int> flow_graph(2 * N + 2);
  for (int i = 0; i < N; ++i) {
    auto itr = dict.find({bx[i], by[i]});
    if (itr != dict.end()) {
      for (const int& from : itr->second) {
        flow_graph.add_edge(from, N + i, 1);
      }
    }
  }

  repeat(i, N) flow_graph.add_edge(s, i, 1);
  repeat_from(i, N, 2 * N) flow_graph.add_edge(i, t, 1);

  int max_flow = flow_graph.flow(s, t);
  if (max_flow == N) {
    cout << "Yes" << endl;
    vector<int> ans(N);
    auto edges = flow_graph.edges();
    for (const auto [from, to, cap, flow] : edges) {
      if (0 <= from && from < N && N <= to && to < 2 * N && flow == 1) {
        // cout << from + 1 << " -> " << to - N + 1 << endl;
        int dx = (bx[to - N] - ax[from]), dy = (by[to - N] - ay[from]);
        // cout << "dx: " << dx << " dy: " << dy << endl;
        if (dx != 0)
          dx /= abs(dx);
        if (dy != 0)
          dy /= abs(dy);
        // cout << "dx: " << dx << " dy: " << dy << endl;
        ans[from] = dir[{dx, dy}] + 1;
      }
    }

    repeat(i, N) { cout << ans[i] << (i == N - 1 ? "\n" : " "); }
  } else {
    cout << "No" << endl;
  }

  return 0;
}