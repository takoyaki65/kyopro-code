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

int N;
int A[100005], B[100005];
vector<int> G[100005];
bool visit[100005];

int main() {
  cin >> N;
  repeat(i, N) cin >> A[i] >> B[i];

  queue<int> que;
  memset(visit, 0, sizeof(visit));

  repeat(i, N) {
    G[A[i] - 1].push_back(i);
    G[B[i] - 1].push_back(i);
    if (A[i] - 1 == i || B[i] - 1 == i) {
      que.push(i);
      visit[i] = true;
    }
  }

  vector<int> ans;
  ans.reserve(N);
  while (!que.empty()) {
    int v = que.front();
    que.pop();
    ans.push_back(v);
    assert(visit[v] == true);
    for (const int& to : G[v]) {
      if (visit[to] == false) {
        visit[to] = true;
        que.push(to);
      }
    }
  }

  if (ans.size() == N) {
    for (int i = N - 1; i >= 0; --i) {
      cout << ans[i] + 1 << endl;
    }
  } else {
    cout << -1 << endl;
  }

  return 0;
}