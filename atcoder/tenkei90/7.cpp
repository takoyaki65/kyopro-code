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

int main() {
  int N, Q;
  cin >> N;
  vector<int> A(N);
  repeat(i, N) cin >> A[i];
  cin >> Q;
  vector<pair<int, int>> B(Q);
  repeat(i, Q) {
    cin >> B[i].first;
    B[i].second = i;
  }

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  // cout << "A: " << endl;
  // repeat(i, N) cout << A[i] << " ";
  // cout << endl;

  // cout << "B: " << endl;
  // repeat(i, Q) cout << "(" << B[i].first << ", " << B[i].second << ") ";
  // cout << endl;

  int idx = 0;
  vector<int> ans(Q);
  repeat(i, Q) {
    int bi = B[i].first;

    while (idx < N && bi > A[idx])
      ++idx;

    // cout << "bi: " << bi << " "
    //      << "idx: " << idx << endl;

    // bi <= A[idx]
    int score = abs(A[min(idx, N - 1)] - bi);
    if (idx - 1 >= 0)
      setmin(score, abs(A[idx - 1] - bi));

    ans[B[i].second] = score;
  }

  repeat(i, Q) { cout << ans[i] << endl; }
  return 0;
}