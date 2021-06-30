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

int main() {
  int n;
  cin >> n;
  auto Graph = vectors(0, n, 0);
  repeat(i, n - 1) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    Graph[a].push_back(b);
    Graph[b].push_back(a);
  }

  vector<int> dist(n, -1);

  auto rec = [&n, &Graph, &dist](auto f, int v, int d) -> void {
    dist[v] = d;

    for (const int& to : Graph[v]) {
      if (dist[to] == -1)
        f(f, to, d + 1);
    }
  };

  rec(rec, 0, 0);

  int s_id = max_element(dist.begin(), dist.end()) - dist.begin();

  dist.assign(n, -1);
  rec(rec, s_id, 0);

  cout << *max_element(dist.begin(), dist.end()) + 1 << endl;

  return 0;
}