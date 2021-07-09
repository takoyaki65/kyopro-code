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

// https://qiita.com/tanaka-a/items/f380257328da421c6584
const int fib[] = {1,  1,  2,   3,   5,   8,   13,  21,   34,
                   55, 89, 144, 233, 377, 610, 987, 1597, 2584};

int dat[2600];

int Ask(int idx) {
  if (dat[idx] == -1) {
    cout << "? " << idx << endl;
    cin >> dat[idx];
  }
  return dat[idx];
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i <= N; ++i)
    dat[i] = -1;
  for (int i = N + 1; i < 2600; ++i)
    dat[i] = -i;

  // 常にright - leftの値をフィボナッチ数にする
  int left = 0, right = 1957;
  for (int idx = 16; idx >= 4; --idx) {
    int c1 = left + fib[idx - 2], c2 = left + fib[idx - 1];
    int f1 = Ask(c1), f2 = Ask(c2);
    if (f1 < f2) {
      left = c1;
    } else {
      right = c2;
    }
  }
  assert(right - left == 3);
  int ans = 0;
  if (left != 0)
    ans = max(ans, Ask(left));
  ans = max(ans, Ask(left + 1));
  ans = max(ans, Ask(left + 2));
  ans = max(ans, Ask(left + 3));
  cout << "! " << ans << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}