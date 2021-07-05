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
int N, Q;
Edge_type E[100005];
Vertex_type G[100005];
bool visit[100005];
int dp[100005];
int K;

int rec(int v) {
  visit[v] = true;
  for (const int& to : G[v]) {
    if (!visit[to]) {
      dp[v] += rec(to);
    }
  }
  return dp[v];
}

int main() {
  cin >> N;
  repeat(i, N - 1) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    G[a].push_back(b);
    G[b].push_back(a);
    E[i] = {a, b};
  }

  cin >> Q;
  while (Q--) {
    cin >> K;
    memset(dp, 0, sizeof(dp));
    memset(visit, false, sizeof(visit));

    repeat(i, K) {
      int v;
      cin >> v;
      --v;
      dp[v] += 1;
    }

    rec(0);

    // for (int i = 0; i < N; ++i) {
    //   cout << "dp[" << i << "] = " << dp[i] << endl;
    // }

    int ans = 0;
    repeat(i, N - 1) {
      auto [a, b] = E[i];
      int val = min(dp[a], dp[b]);
      if ((0 < val && val < K))
        ++ans;
    }
    cout << ans << endl;
  }

  return 0;
}