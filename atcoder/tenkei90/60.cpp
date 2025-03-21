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
int A[300005];
int LIS[300005];
int L[300005], R[300005];
const int INF = 4000000;

int main() {
  cin >> N;
  repeat(i, N) cin >> A[i];

  repeat(i, N) LIS[i] = INF;
  repeat(i, N) {
    int j = lower_bound(LIS, LIS + N, A[i]) - LIS;
    LIS[j] = A[i];
    L[i] = j + 1;
  }
  repeat(i, N) LIS[i] = INF;
  for (int i = N - 1; i >= 0; --i) {
    int j = lower_bound(LIS, LIS + N, A[i]) - LIS;
    LIS[j] = A[i];
    R[i] = j + 1;
  }

  int ans = 0;
  for (int i = 0; i < N; ++i)
    ans = max(ans, L[i] + R[i] - 1);
  cout << ans << endl;

  return 0;
}