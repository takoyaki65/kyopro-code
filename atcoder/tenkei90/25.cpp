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

long long ans = 0;
int num[13];
int elem[13];
int elem1[13];
long long N, B;
long long base[] = {1L,         10L,         100L,         1000L,
                    10000L,     100000L,     1000000L,     10000000L,
                    100000000L, 1000000000L, 10000000000L, 100000000000L};

void rec(const int idx, const long long fm) {
  if (idx >= 12)
    return;
  int prev = (idx == 0) ? 0 : num[idx - 1];
  // idx桁にprev~9の数字を付けていく
  for (int i = prev; i <= 9; ++i) {
    num[idx] = i;
    ++elem[i];
    long long m = (fm * i) + B;
    if (i != 0 && 1 <= m && m <= N) {
      memset(elem1, 0, sizeof(elem1));
      long long tmp = m;
      while (tmp) {
        ++elem1[tmp % 10];
        tmp /= 10;
      }
      bool flg = true;
      for (int j = 0; j < 13; ++j)
        if (elem1[j] != elem[j])
          flg = false;
      if (flg) {
        // cout << m << endl;
        ++ans;
      }
    }
    rec(idx + 1, fm * i);
    --elem[i];
  }
}

int main() {
  cin >> N >> B;
  rec(0, 1);
  cout << ans << endl;
  return 0;
}