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

using pii = pair<int, int>;

int main() {
  int N, M;
  cin >> N >> M;
  vector<pii> LR(M);
  repeat(i, M) {
    cin >> LR[i].first >> LR[i].second;
    --LR[i].first, --LR[i].second;
  }
  // sort(LR.begin(), LR.end());

  // comp := 余事象
  long long comp = 0;
  {
    long long add1 = 0;
    vector<long long> cnt(N, 0);
    repeat(i, M)++ cnt[LR[i].first], ++cnt[LR[i].second];
    repeat(i, N) comp += cnt[i] * (cnt[i] - 1) / 2,
        add1 += cnt[i] * (cnt[i] - 1) / 2;
    // cout << "add1: " << add1 << endl;
  }

  {
    // v[i] := LR[i].second <= i であるような個数
    long long add2 = 0;
    vector<int> v(N, 0);
    repeat(i, M)++ v[LR[i].second];
    repeat(i, N - 1) v[i + 1] += v[i];
    repeat(i, M) if (LR[i].first - 1 >= 0) comp += v[LR[i].first - 1],
        add2 += v[LR[i].first - 1];
    // cout << "add2: " << add2 << endl;
  }

  {
    long long add3 = 0;
    vector<pii> RL = LR;
    repeat(i, M) swap(RL[i].first, RL[i].second);
    sort(RL.begin(), RL.end());
    // repeat(i, M) cout << "(" << RL[i].second << ", " << RL[i].first << ")"
    //                   << endl;
    vector<int> v(N, 0);
    repeat(i, M) {
      // Rの小さい順に見ていく(Rが同じなら,Lの小さい順)
      for (int j = RL[i].second + 1; j < RL[i].first; ++j) {
        comp += v[j];
        add3 += v[j];
      }
      ++v[RL[i].second];
    }
    // cout << "add3: " << add3 << endl;
  }

  long long all = (long long)M * (M - 1) / 2;
  // cout << "all: " << all << endl;

  cout << all - comp << endl;

  return 0;
}