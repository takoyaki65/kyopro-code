#include <algorithm>
#include <array>
#include <bitset>
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
#define bit_stand(n, k) ((n >> k) & 1)
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
int A[100005];

long double bsearch_average() {
  long double low = 0, high = 1e9 + 10;
  vector<long double> f(N + 1, 0), g(N + 1, 0);

  while (abs(high - low) > 1e-9) {
    long double average = low + (high - low) / 2;
    f[0] = 0, g[0] = 0;
    for (int i = 0; i < N; ++i) {
      f[i + 1] = max(f[i], g[i]) + (long double)A[i] - average;
      g[i + 1] = f[i];
    }
    long double val = max(f[N], g[N]);
    if (val < 0.0)
      high = average;
    else
      low = average;
  }
  return low;
}

int bsearch_median() {
  int low = 0, high = 1000000010;
  vector<int> f(N + 1, 0), g(N + 1, 0);

  while (abs(high - low) > 1) {
    int median = low + (high - low) / 2;
    f[0] = 0, g[0] = 0;
    for (int i = 0; i < N; ++i) {
      f[i + 1] = max(f[i], g[i]) + (A[i] >= median ? 1 : -1);
      g[i + 1] = f[i];
    }
    int val = max(f[N], g[N]);
    if (val <= 0)
      high = median;
    else
      low = median;
  }
  return low;
}

int main() {
  cin >> N;
  for (int i = 0; i < N; ++i)
    cin >> A[i];

  cout << fixed << setprecision(5) << bsearch_average() << endl;
  cout << bsearch_median() << endl;
  return 0;
}