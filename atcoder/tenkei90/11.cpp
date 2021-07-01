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

struct task {
  int d, c;
  long long s;
  bool operator<(const task& rhs) const { return d < rhs.d; }
};

int N;
long long dp[5001][5001];
task vtask[5001];

int main() {
  cin >> N;
  repeat(i, N) cin >> vtask[i].d >> vtask[i].c >> vtask[i].s;
  sort(vtask, vtask + N);

  // dp[i][j] := [0, i)までの仕事を見終え、合計仕事時間がjの時の最大報酬
  repeat(i, N) {
    auto [d, c, s] = vtask[i];
    repeat(j, 5001) {
      if (c <= j && j <= d) {
        dp[i + 1][j] = max(dp[i][j], dp[i][j - c] + s);
      } else {
        dp[i + 1][j] = dp[i][j];
      }
    }
  }

  cout << *max_element(dp[N], dp[N] + 5001) << endl;
  return 0;
}