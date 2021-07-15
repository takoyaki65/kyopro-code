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

struct edge {
  // good := 辺の縁起がいいかどうか
  int to, good, cost;
};

int N, D;
vector<edge> G[100005];
int dist1[100005], dist2[100005];
int flip[100005];

void rec1(int v, int par, int cost, int* d) {
  d[v] = cost;
  for (const edge& e : G[v]) {
    if (e.to == par)
      continue;
    rec1(e.to, v, cost + e.cost, d);
  }
}

int rec2(int v, int par) {
  int ret = 0;
  for (const edge& e : G[v]) {
    if (e.to == par)
      continue;
    if (e.good == 1)
      ret += 1 + rec2(e.to, v);
    else
      ret += rec2(e.to, v);
  }
  return ret;
}

void rec3(int v, int par, int cnt) {
  flip[v] = cnt;
  for (const edge& e : G[v]) {
    if (e.to == par)
      continue;
    if (e.good == 1)
      rec3(e.to, v, cnt - 1);
    else
      rec3(e.to, v, cnt + 1);
  }
}

const int INF = 1 << 30;

int main() {
  cin >> N >> D;
  repeat(i, N - 1) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    G[a].push_back({b, 1, c});
    G[b].push_back({a, 0, c});
  }

  rec1(0, -1, 0, dist1);
  const int v1 = max_element(dist1, dist1 + N) - dist1;
  rec1(v1, -1, 0, dist1);
  const int v2 = max_element(dist1, dist1 + N) - dist1;
  rec1(v2, -1, 0, dist2);

  flip[0] = rec2(0, -1);
  rec3(0, -1, flip[0]);

  int ans = INF;
  for (int i = 0; i < N; ++i) {
    int maxDist = max(dist1[i], dist2[i]);
    int flipCnt = flip[i];
    if (maxDist <= D) {
      ans = min(ans, flipCnt);
    }
  }

  cout << (ans == INF ? -1 : ans) << endl;
  return 0;
}