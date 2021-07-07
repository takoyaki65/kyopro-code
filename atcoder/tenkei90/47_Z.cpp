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

// https://snuke.hatenablog.com/entry/2014/12/03/214243
void Zarray(const string& S, vector<int>& Z) {
  const int n = S.size();
  if (Z.size() != n)
    Z.assign(n, 0);
  Z[0] = n;
  // i := 現在見ている文字の先頭
  // j := 共通接頭辞の長さ
  int i = 1, j = 0;
  while (i < n) {
    while (i + j < n && S[j] == S[i + j])
      j += 1;
    Z[i] = j;
    if (j == 0) {
      i += 1;
      continue;
    }
    int k = 1;
    while (i + k < n && k + Z[k] < j)
      Z[i + k] = Z[k], k += 1;
    i += k;
    j -= k;
  }
}

const char rgb[] = "RGB";

int solve(const string& S, const string& T) {
  assert(S.size() == T.size());
  const int n = S.size();

  int ret = 0;
  string Zstr = S + '$' + T;
  assert(Zstr.size() == 2 * n + 1);
  vector<int> Z(Zstr.size());
  for (int i = 0; i < 3; ++i) {
    char ch1 = rgb[i], ch2 = rgb[(i + 1) % 3];
    for (int j = n + 1; j < 2 * n + 1; ++j) {
      assert(0 <= j && j < Zstr.size());
      if (Zstr[j] == ch1)
        Zstr[j] = ch2;
      else if (Zstr[j] == ch2)
        Zstr[j] = ch1;
    }
    // cout << "Zstr: " << Zstr << endl;
    Zarray(Zstr, Z);
    for (int k = 0; k < n; ++k) {
      assert(n + 1 + k < Z.size());
      int len = n - k;
      if (Z[n + 1 + k] == len)
        ret += 1;
    }
    // 元に戻す
    for (int j = n + 1; j < 2 * n + 1; ++j) {
      assert(0 <= j && j < Zstr.size());
      if (Zstr[j] == ch1)
        Zstr[j] = ch2;
      else if (Zstr[j] == ch2)
        Zstr[j] = ch1;
    }
  }
  return ret;
}

int ch2bit(char ch) {
  if (ch == 'R')
    return 0;
  if (ch == 'G')
    return 1;
  return 2;
}

int main() {
  int N;
  cin >> N;
  string S, T;
  cin >> S >> T;

  // グリッドの対角線上の色が全て同じになるかチェック
  int diag = 0;
  {
    int rgb_count[3] = {0, 0, 0};
    for (int i = 0; i < N; ++i) {
      int ch1 = ch2bit(S[i]), ch2 = ch2bit(T[i]);
      if (ch1 == ch2)
        rgb_count[ch1] += 1;
      else
        rgb_count[3 ^ (ch1 | ch2)] += 1;
    }
    if (rgb_count[0] == N || rgb_count[1] == N || rgb_count[2] == N) {
      diag += 1;
    }
  }

  int ans = solve(S, T) + solve(T, S) - diag;

  cout << ans << endl;

  return 0;
}