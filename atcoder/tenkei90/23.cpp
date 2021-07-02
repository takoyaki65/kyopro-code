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

char str[30][30];
int H, W;
int kx[600], ky[600];

int ans;
const int MOD = 1000000007;

// cnt := 置いたキングの数
void rec(int x, int y, int cnt) {
  if (x >= H) {
    ++ans;
    if (ans >= MOD)
      ans -= MOD;

    return;
  }

  int nx = x, ny = y + 1;
  if (ny >= W)
    ++nx, ny = 0;

  // キングを置かない
  rec(nx, ny, cnt);

  // キングを置く
  if (str[x][y] == '#')
    return;
  for (int i = 0; i < cnt; ++i) {
    if (abs(x - kx[i]) <= 1 && abs(y - ky[i]) <= 1)
      return;
  }
  kx[cnt] = x, ky[cnt] = y;
  rec(nx, ny, cnt + 1);
}

int main() {
  cin >> H >> W;
  repeat(i, H) cin >> str[i];

  rec(0, 0, 0);
  cout << ans << endl;

  return 0;
}