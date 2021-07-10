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

int H, W;
long long A[110][110], B[110][110], C[110][110];

int main() {
  cin >> H >> W;
  repeat(i, H) repeat(j, W) cin >> A[i][j];
  repeat(i, H) repeat(j, W) cin >> B[i][j];
  repeat(i, H) repeat(j, W) C[i][j] = A[i][j] - B[i][j];

  long long ans = 0;
  repeat(i, H - 1) repeat(j, W - 1) {
    long long dif = C[i][j];
    ans += abs(C[i][j]);
    repeat(dx, 2) repeat(dy, 2) C[i + dx][j + dy] -= dif;
  }

  repeat(i, H) repeat(j, W) {
    if (C[i][j] != 0) {
      cout << "No" << endl;
      return 0;
    }
  }

  cout << "Yes" << endl;
  cout << ans << endl;

  return 0;
}