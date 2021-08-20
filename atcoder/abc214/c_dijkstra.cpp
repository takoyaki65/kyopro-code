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

typedef pair<int, int> pii;
typedef vector<vector<pii>> Graph_type;

void dijkstra(const Graph_type& G, int s, vector<int>& dist) {
  const int n = G.size();
  dist.assign(n, -1);
  priority_queue<pii, vector<pii>, greater<pii>> que;
  que.push({0, s});
  while (!que.empty()) {
    auto [len, cur] = que.top();
    que.pop();
    if (dist[cur] != -1)
      continue;
    dist[cur] = len;
    for (const auto& [to, cost] : G[cur]) {
      if (dist[to] == -1) {
        que.push({len + cost, to});
      }
    }
  }
  return;
}

int main() {
  int n;
  cin >> n;
  vector<int> s(n), t(n);
  repeat(i, n) cin >> s[i];
  repeat(i, n) cin >> t[i];
  Graph_type G(n + 1);
  repeat(i, n) G[i].push_back({(i + 1) % n, s[i]});
  repeat(i, n) G[n].push_back({i, t[i]});

  vector<int> ans;
  dijkstra(G, n, ans);
  repeat(i, n) cout << ans[i] << endl;

  return 0;
}