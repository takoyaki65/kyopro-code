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
#define bit_stand(n, k) ((n >> k) & 1)
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
int K;

const int MAX_N = 6;
const int MAX_K = 6;
// min_query[l][r] := arr[l,r)の最小値
int min_query[10][10];
int arr[10];

int rec(int cur) {
  if (cur == N) {
    for (int l = 0; l < N; ++l) {
      min_query[l][l + 1] = arr[l];
    }
    for (int w = 2; w <= N; ++w) {
      for (int l = 0; l + w <= N; ++l) {
        int r = l + w;
        min_query[l][r] = min(arr[l], min_query[l + 1][r]);
      }
    }

    for (int l = 0; l < N; ++l) {
      for (int r = l + 1; r <= N; ++r) {
        if (min_query[l][r] * (r - l) > K)
          return 0;
      }
    }

    return 1;
  }

  int ret = 0;
  for (int i = 0; i <= K; ++i) {
    arr[cur] = i;
    ret += rec(cur + 1);
  }
  return ret;
}

int main() {
  cin >> N >> K;
  if (N > MAX_N || K > MAX_K) {
    cout << "error" << endl;
    return 0;
  }

  cout << rec(0) << endl;

  return 0;
}