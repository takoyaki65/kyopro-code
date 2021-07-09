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

int N;
long long K;
int dp[64][100005];

int Calc(int X) {
  int Y = 0, Z = X;
  while (Z) {
    Y += Z % 10;
    Z /= 10;
  }
  return (X + Y) % 100000;
}

int main() {
  cin >> N >> K;
  repeat(i, 100005) dp[0][i] = Calc(i);

  repeat_from(i, 1, 64) {
    repeat(j, 100005) { dp[i][j] = dp[i - 1][dp[i - 1][j]]; }
  }

  int ans = N;
  repeat(i, 64) {
    if ((K >> i) & 1) {
      // cout << "i: " << i << endl;
      // cout << ans << " -> " << dp[i][ans] << endl;
      ans = dp[i][ans];
    }
  }

  cout << ans << endl;

  return 0;
}