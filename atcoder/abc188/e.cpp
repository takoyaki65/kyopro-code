#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
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

// 「町iで金を買うとして，町i以降で金を売るときに，最も高く売れる値段」
// を再帰関数を用いて求める
int rec(const std::vector<std::vector<int>>& graph,
        const std::vector<int>& va,
        std::vector<int>& res,
        int i) {
  if (res[i] != -1)
    return std::max(va[i], res[i]);
  res[i] = 0;
  for (int to : graph[i]) {
    res[i] = std::max(res[i], rec(graph, va, res, to));
  }
  return std::max(va[i], res[i]);
}

int main() {
  int n, m;
  cin >> n >> m;
  std::vector<int> va(n);
  repeat(i, n) cin >> va[i];
  auto graph = vectors(0, n, 0);
  repeat(i, m) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    graph[x].push_back(y);
  }

  std::vector<int> res(n, -1);
  repeat(i, n) { rec(graph, va, res, i); }

  long long ans = std::numeric_limits<long long>::min();
  repeat(i, n)
      // 必ず売らなきゃいけないので，先端部分は考慮しない
      if (graph[i].size() != 0) ans = std::max(ans, (long long)res[i] - va[i]);
  std::cout << ans << std::endl;
  return 0;
}