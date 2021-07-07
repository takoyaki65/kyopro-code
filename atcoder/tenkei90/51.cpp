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

int N, K;
long long P;
long long A[50];
// L[i] := 左半分のグループからi個選んだ時の値段リスト
vector<long long> L[50], R[50];

int main() {
  cin >> N >> K >> P;
  repeat(i, N) cin >> A[i];

  vector<long long> la, ra;
  repeat(i, N / 2) la.push_back(A[i]);
  repeat_from(i, N / 2, N) ra.push_back(A[i]);

  int Lsize = la.size();
  for (int bit = 0; bit < (1 << Lsize); ++bit) {
    int cnt = 0;
    long long cost = 0;
    for (int i = 0; i < Lsize; ++i) {
      if ((bit >> i) & 1) {
        cnt += 1;
        cost += la[i];
      }
    }
    if (cost <= P) {
      L[cnt].push_back(cost);
    }
  }
  for (int cnt = 0; cnt < Lsize; ++cnt)
    sort(L[cnt].begin(), L[cnt].end());
  int Rsize = ra.size();
  for (int bit = 0; bit < (1 << Rsize); ++bit) {
    int cnt = 0;
    long long cost = 0;
    for (int i = 0; i < Rsize; ++i) {
      if ((bit >> i) & 1) {
        cnt += 1;
        cost += ra[i];
      }
    }
    if (cost <= P) {
      R[cnt].push_back(cost);
    }
  }
  for (int cnt = 0; cnt < Rsize; ++cnt)
    sort(R[cnt].begin(), R[cnt].end());

  long long ans = 0;
  for (int lcnt = 0; lcnt <= K; ++lcnt) {
    int rcnt = K - lcnt;
    // 2分探索
    // for (const auto& cost : L[lcnt]) {
    //   long long remain = P - cost;
    //   ans += upper_bound(R[rcnt].begin(), R[rcnt].end(), remain + 1) -
    //          R[rcnt].begin();
    // }

    // 尺取り法
    int cur = R[rcnt].size();
    for (const auto& cost : L[lcnt]) {
      long long remain = P - cost;
      while (cur >= 1 && R[rcnt][cur - 1] > remain)
        cur -= 1;
      ans += cur;
    }
  }

  cout << ans << endl;

  return 0;
}