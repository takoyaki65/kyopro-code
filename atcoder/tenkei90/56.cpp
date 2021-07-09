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

int N, S;
bool dp[101][100005];
int A[101], B[101];
char ans[102];

int main() {
  cin >> N >> S;
  dp[0][0] = true;
  repeat(i, N) cin >> A[i] >> B[i];
  repeat(i, N) {
    repeat_from(j, A[i], S + 1) { dp[i + 1][j] |= dp[i][j - A[i]]; }
    repeat_from(j, B[i], S + 1) { dp[i + 1][j] |= dp[i][j - B[i]]; }
  }

  // dp[N][S]から経路復元
  ans[N] = '\0';
  int i = N - 1, j = S;
  while (i >= 0) {
    if (j >= A[i] && dp[i][j - A[i]]) {
      ans[i] = 'A';
      j = j - A[i];
    } else if (j >= B[i] && dp[i][j - B[i]]) {
      ans[i] = 'B';
      j = j - B[i];
    } else {
      break;
    }
    --i;
  }
  if (i >= 0) {
    cout << "Impossible" << endl;
  } else {
    cout << ans << endl;
  }

  return 0;
}