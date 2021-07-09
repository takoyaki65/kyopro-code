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
using pii = pair<int, int>;

int N, M;
int vertex_num;
Vertex_type G[200005];
int dist[200005];

int main() {
  cin >> N >> M;
  vertex_num = N;
  repeat(i, M) {
    int K;
    cin >> K;
    repeat(i, K) {
      int R;
      cin >> R;
      --R;
      G[vertex_num].push_back(R);
      G[R].push_back(vertex_num);
    }
    vertex_num += 1;
  }

  memset(dist, -1, sizeof(dist));
  queue<int> que;
  dist[0] = 0;
  que.push(0);
  while (!que.empty()) {
    int v = que.front();
    que.pop();
    assert(dist[v] != -1);
    for (const int& to : G[v]) {
      if (dist[to] == -1) {
        dist[to] = dist[v] + 1;
        que.push(to);
      }
    }
  }

  for (int i = 0; i < N; ++i) {
    cout << (dist[i] < 0 ? -1 : dist[i] / 2) << endl;
  }

  return 0;
}