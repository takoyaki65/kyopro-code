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

using Edge_type = pair<int, int>;
using Vertex_type = vector<int>;

int N;
Vertex_type G[100005];
Edge_type E[100005];
int dp[100005];

int rec(int v, int p) {
  int ret = 1;
  for (const int& to : G[v]) {
    if (to != p) {
      ret += rec(to, v);
    }
  }
  return dp[v] = ret;
}

int main() {
  int N;
  cin >> N;
  repeat(i, N - 1) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    G[a].push_back(b);
    G[b].push_back(a);
    E[i] = {a, b};
  }

  rec(0, -1);

  long long ans = 0;
  repeat(i, N - 1) {
    auto [u, v] = E[i];
    int val = min(dp[u], dp[v]);
    // cout << "(u,v,val) = (" << u << "," << v << "," << val << ")" << endl;
    ans += (long long)val * (N - val);
  }
  cout << ans << endl;

  return 0;
}