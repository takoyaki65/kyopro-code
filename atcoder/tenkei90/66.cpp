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
int L[110], R[110];

int main() {
  cin >> N;
  repeat(i, N) cin >> L[i] >> R[i];

  double ans = 0;
  repeat(i, N) repeat_from(j, i + 1, N) {
    // A[i] > A[j]となる確率を調べる
    // 期待値 = 転倒数1 × (A[i] > A[j]となる確率)
    int cnt = 0;
    repeat_from(ai, L[i], R[i] + 1) repeat_from(aj, L[j], R[j] + 1) {
      if (ai > aj)
        cnt += 1;
    }

    ans += (double)cnt / ((R[i] - L[i] + 1) * (R[j] - L[j] + 1));
  }

  cout << fixed << setprecision(10) << ans << endl;
  return 0;
}