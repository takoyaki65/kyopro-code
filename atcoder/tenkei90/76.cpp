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
long long A[200005];

int main() {
  cin >> N;
  repeat(i, N) cin >> A[i];
  repeat_from(i, N, 2 * N) A[i] = A[i - N];

  long long all = 0;
  repeat(i, N) all += A[i];
  if (all % 10) {
    cout << "No" << endl;
    return 0;
  }
  const long long goal = all / 10;

  long long sum = 0;
  int r = 0;
  // 尺取り法(sliding window)
  for (int l = 0; l < N; ++l) {
    while (r < l + N && sum < goal) {
      sum += A[r];
      r += 1;
    }
    if (sum == goal) {
      // cout << "l: " << l << "r: " << r << " sum: " << sum << endl;
      cout << "Yes" << endl;
      return 0;
    }
    sum -= A[l];
  }

  cout << "No" << endl;

  return 0;
}