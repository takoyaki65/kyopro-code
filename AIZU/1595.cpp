// https://onlinejudge.u-aizu.ac.jp/problems/1595
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
vector<int> G[100005];
int dist1[100005], dist2[100005];

void rec(int v, int par, int depth, int* d) {
  d[v] = depth;
  for (const int& to : G[v]) {
    if (to == par)
      continue;
    rec(to, v, depth + 1, d);
  }
  return;
}

int main() {
  cin >> N;
  int edgeSize = 0;
  repeat(i, N - 1) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    G[u].push_back(v);
    G[v].push_back(u);
    edgeSize += 1;
  }

  rec(0, -1, 0, dist1);
  int v1 = max_element(dist1, dist1 + N) - dist1;
  rec(v1, -1, 0, dist1);
  int v2 = max_element(dist1, dist1 + N) - dist1;
  rec(v2, -1, 0, dist2);

  for (int i = 0; i < N; ++i) {
    cout << edgeSize * 2 - max(dist1[i], dist2[i]) << endl;
  }

  return 0;
}