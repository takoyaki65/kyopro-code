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
inline int sz(T &x) {
  return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T &a, T b) {
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
  int a, b, c;
  cin >> a >> b >> c;
  const int max_num =
      (a > 0 ? 100 - a : 0) + (b > 0 ? 100 - b : 0) + (c > 0 ? 100 - c : 0);
  auto dp = vectors(0.0, max_num + 20, 101, 101, 101);
  dp[0][a][b][c] = 1.0;
  double res = 0.0;
  for (int i = 0; i < max_num + 10; ++i) {
    repeat_from(gold, 0, 100) {
      repeat_from(silver, 0, 100) {
        repeat_from(cupper, 0, 100) {
          double prob = dp[i][gold][silver][cupper];
          int tot = gold + silver + cupper;
          if (tot <= 0) continue;
          dp[i + 1][gold + 1][silver][cupper] += prob * gold / tot;
          dp[i + 1][gold][silver + 1][cupper] += prob * silver / tot;
          dp[i + 1][gold][silver][cupper + 1] += prob * cupper / tot;
        }
      }
    }

    repeat_from(j, 0, 100) {
      repeat_from(k, 0, 100) {
        res += (i + 1) * (dp[i + 1][100][j][k] + dp[i + 1][j][100][k] +
                          dp[i + 1][j][k][100]);
      }
    }
  }
  cout << fixed << setprecision(10) << res << endl;
  return 0;
}