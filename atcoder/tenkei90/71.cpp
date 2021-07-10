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

int N, M, K;
int in_deg[100005];
vector<int> G[100005];

vector<int> stk;
vector<int> memo;
vector<vector<int>> ans;

bool rec(int cur) {
  if (cur == N) {
    ans.push_back(memo);
    return true;
  }
  if (stk.size() == 0)
    return false;

  for (int i = (int)stk.size() - 1; i >= 0; --i) {
    if (ans.size() == K) {
      break;
    }
    int x = stk[i];

    // 頂点xを使う
    memo[cur] = x;
    stk.erase(stk.begin() + i);
    for (const int& to : G[x]) {
      in_deg[to] -= 1;
      if (in_deg[to] == 0) {
        stk.push_back(to);
      }
    }
    bool flag = rec(cur + 1);
    if (flag == false)
      return false;

    // 元に戻す
    for (const int& to : G[x]) {
      if (in_deg[to] == 0)
        stk.pop_back();
      in_deg[to] += 1;
    }
    stk.insert(stk.begin() + i, x);
  }
  return true;
}

int main() {
  cin >> N >> M >> K;
  repeat(i, M) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    G[a].push_back(b);
    in_deg[b] += 1;
  }

  repeat(i, N) {
    if (in_deg[i] == 0) {
      stk.push_back(i);
    }
  }

  memo.assign(N, -1);

  rec(0);
  if (ans.size() < K) {
    cout << -1 << endl;
  } else {
    for (int i = 0; i < K; ++i) {
      for (int j = 0; j < N; ++j) {
        cout << ans[i][j] + 1 << (j == N - 1 ? "\n" : " ");
      }
    }
  }

  return 0;
}