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

int N, M;
vector<int> G[200005];
int Q;
int X[200005], Y[200005];
int E[200005], largeE[200005];
vector<int> largeV;
vector<int> G_large[200005];

int main() {
  cin >> N >> M;
  repeat(i, M) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  int Q;
  cin >> Q;
  repeat(i, Q) {
    cin >> X[i] >> Y[i];
    X[i] -= 1;
  }

  int B = int(sqrt(2 * M));
  // cout << "B: " << B << endl;
  repeat(i, N) {
    if (G[i].size() >= B)
      largeV.push_back(i);
  }

  for (const int& lv : largeV) {
    for (const int& from : G[lv]) {
      G_large[from].push_back(lv);
    }
    G_large[lv].push_back(lv);
  }

  repeat(i, N) E[i] = -1, largeE[i] = -1;
  repeat(i, Q) {
    int x = X[i];
    int recent = E[x];
    for (const int& to : G_large[x]) {
      recent = max(recent, largeE[to]);
    }
    cout << (recent == -1 ? 1 : Y[recent]) << endl;
    if (G[x].size() >= B) {
      largeE[x] = i;
    } else {
      E[x] = i;
      for (const int& to : G[x]) {
        E[to] = i;
      }
    }
  }

  return 0;
}