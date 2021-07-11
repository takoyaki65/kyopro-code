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

long long A[30];

int main() {
  int N, D;
  cin >> N >> D;
  repeat(i, N) cin >> A[i];

  long long ans = 1LL << D;
  long long sub = 0;
  repeat_from(bit, 1, 1 << N) {
    long long val = 0;
    int cnt = 0;
    repeat(i, N) if ((bit >> i) & 1LL) val |= A[i], cnt += 1;

    val = val ^ ((1LL << D) - 1LL);

    int p = __builtin_popcount(val) + __builtin_popcount(val >> 32);
    if (cnt % 2)
      sub += (1LL << p);
    else
      sub -= (1LL << p);
  }

  ans -= sub;
  cout << ans << endl;

  return 0;
}