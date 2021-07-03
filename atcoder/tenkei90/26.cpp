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

int N;
Graph_type G;
int color[100005];

void rec(int v, int col) {
  color[v] = col;
  for (const int& to : G[v]) {
    if (color[to] == -1) {
      rec(to, 1 - col);
    }
  }
}

int main() {
  cin >> N;
  G.assign(N, Vertex_type());
  repeat(i, N - 1) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  memset(color, -1, sizeof(color));
  rec(0, 0);

  int c0 = 0, c1 = 0;
  repeat(i, N) if (color[i] == 0) c0 += 1;
  else c1 += 1;

  int ans = (c0 >= c1) ? 0 : 1;
  int cnt = 0;
  repeat(i, N) {
    if (color[i] == ans) {
      cout << i + 1 << (cnt == N / 2 - 1 ? "\n" : " ");
      ++cnt;
    }
    if (cnt >= N / 2)
      break;
  }

  return 0;
}