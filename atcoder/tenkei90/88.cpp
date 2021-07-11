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

int N, Q;
int A[110];
int X[5000], Y[5000];
vector<int> G[110];

int ans_sum = 0;

// combination[S] := 総和Sの選び方
vector<vector<int>> combination[9000];

bool used[110];
int C[110];

bool rec(int idx) {
  if (idx == N) {
    int sum = 0;
    vector<int> list;
    repeat(i, N) if (used[i]) {
      list.push_back(i);
      sum += A[i];
    }
    if (list.size() > 0)
      combination[sum].push_back(list);
    if (combination[sum].size() >= 2) {
      ans_sum = sum;
      return true;
    }
    return false;
  }
  // idx番目を選ばない
  if (rec(idx + 1))
    return true;

  // idx番目を選ぶ
  if (C[idx] == 0) {
    used[idx] = true;
    for (const int& to : G[idx]) {
      C[to] += 1;
    }
    if (rec(idx + 1))
      return true;
    used[idx] = false;
    for (const int& to : G[idx]) {
      C[to] -= 1;
    }
  }
  return false;
}

int main() {
  cin >> N >> Q;
  repeat(i, N) cin >> A[i];
  repeat(i, Q) {
    cin >> X[i] >> Y[i];
    X[i] -= 1, Y[i] -= 1;
    if (X[i] > Y[i])
      swap(X[i], Y[i]);
  }

  repeat(i, Q) { G[X[i]].push_back(Y[i]); }

  rec(0);

  for (int i = 0; i < 2; ++i) {
    int seq_size = combination[ans_sum][i].size();
    cout << seq_size << endl;
    for (int j = 0; j < seq_size; ++j) {
      cout << combination[ans_sum][i][j] + 1
           << (j == seq_size - 1 ? "\n" : " ");
    }
  }

  return 0;
}