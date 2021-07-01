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

using pii = pair<int, int>;

int main() {
  int N, M;
  cin >> N >> M;
  vector<pii> LR(M);
  repeat(i, M) {
    cin >> LR[i].first >> LR[i].second;
    --LR[i].first, --LR[i].second;
  }
  sort(LR.begin(), LR.end());

  long long ans = 0;
  for (int i = 0; i < M; i++) {
    auto [l, r] = LR[i];
    // [l+1, r)
    int st = lower_bound(LR.begin(), LR.end(), pii{l + 1, -1}) - LR.begin();
    int en = upper_bound(LR.begin(), LR.end(), pii{r, -1}) - LR.begin();

    // さらに、Rの範囲が[0, l), または[r+1, N)のものを探す
    for (int j = st; j < en; ++j) {
      assert(0 <= j && j < M);
      auto [pl, pr] = LR[j];
      assert(l + 1 <= pl && pl < r);
      if ((0 <= pr && pr < l) || (r + 1 <= pr && pr < N))
        ++ans;
    }
  }

  cout << ans << endl;

  return 0;
}