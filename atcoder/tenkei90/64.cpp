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

int N, Q;
int A[100005];
long long dif[100005];

int main() {
  cin >> N >> Q;
  repeat_from(i, 1, N + 1) cin >> A[i];

  long long ans = 0;
  repeat(i, N + 1) { dif[i] = A[i] - A[i + 1]; }
  repeat_from(i, 1, N) ans += abs(dif[i]);

  // cout << "0: " << endl;
  // repeat(i, N + 1) cout << dif[i] << " ";
  // cout << endl;
  // cout << "ans: " << ans << endl;

  int cnt = 1;

  while (Q--) {
    int l, r, v;
    cin >> l >> r >> v;

    long long lv = dif[l - 1];
    dif[l - 1] -= v;
    if (l - 1 >= 1)
      ans = ans - abs(lv) + abs(dif[l - 1]);

    long long rv = dif[r];
    dif[r] += v;
    if (r < N)
      ans = ans - abs(rv) + abs(dif[r]);

    // cout << cnt++ << ": " << endl;
    // repeat(i, N + 1) cout << dif[i] << " ";
    // cout << endl;

    cout << ans << endl;
  }

  return 0;
}