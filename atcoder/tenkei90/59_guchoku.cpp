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

int N, M, Q;
vector<int> G[100005];
int A[100005], B[100005];
bool visit[100005];

void rec(int v) {
  visit[v] = true;
  for (const int& to : G[v]) {
    if (visit[to] == false) {
      rec(to);
    }
  }
}

int main() {
  cin >> N >> M >> Q;
  repeat(i, M) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    G[x].push_back(y);
  }
  repeat(i, Q) {
    cin >> A[i] >> B[i];
    --A[i], --B[i];
  }

  repeat(i, Q) {
    memset(visit, false, sizeof(visit));
    rec(A[i]);
    if (visit[B[i]]) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }

  return 0;
}