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

int N, M;
const int INF = 1000000000;
using Edge_type = pair<int, int>;
int dist[420][420];
vector<Edge_type> G[420];

int main() {
  cin >> N >> M;
  repeat(i, M) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    G[a].push_back({b, c});
  }

  repeat(i, N) repeat(j, N) dist[i][j] = INF;
  repeat(i, N) dist[i][i] = 0;
  repeat(i, N) {
    for (const auto& [to, cost] : G[i]) {
      dist[i][to] = cost;
    }
  }

  long long ans = 0;
  repeat(k, N) {
    repeat(i, N) repeat(j, N) dist[i][j] =
        min(dist[i][j], dist[i][k] + dist[k][j]);

    repeat(i, N) repeat(j, N) if (dist[i][j] != INF) ans += dist[i][j];
  }

  cout << ans << endl;
  return 0;
}