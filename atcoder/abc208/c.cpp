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
using ll = long long;

ll N, K;

pair<int, ll> a[200005];
ll ans[200005];
unordered_map<int, int> Map;

int main() {
  cin >> N >> K;
  repeat(i, N) {
    cin >> a[i].first;
    --a[i].first;
    a[i].second = 0;
    Map[a[i].first] = i;
  }

  sort(a, a + N);
  {
    ll add = K / N;
    K = K - add * N;
    repeat(i, N) a[i].second += add;
  }

  repeat(i, K) a[i].second += 1;
  repeat(i, N) { ans[Map[a[i].first]] = a[i].second; }
  repeat(i, N) cout << ans[i] << endl;
  return 0;
}