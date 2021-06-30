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

// TLE解

int N, K;
string S;
string ans;
char str[100005];

void rec(int cur, int idx) {
  if (cur == K) {
    if (ans > str)
      ans = str;
    return;
  }
  if (idx >= N || (K - cur > N - idx))
    return;

  // idx番の文字を選ぶ
  str[cur] = S[idx];
  rec(cur + 1, idx + 1);
  // idx番目の文字を選ばない
  rec(cur, idx + 1);
}

int main() {
  cin >> N >> K >> S;

  str[N] = '\0';
  ans = string(N, 'z');
  rec(0, 0);
  cout << ans << endl;

  return 0;
}