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
int X[100005], Y[100005];

long long score(int ax, int ay) {
  long long ret = 0;
  repeat(i, N) {
    ret += abs(X[i] - ax);
    ret += abs(Y[i] - ay);
  }
  return ret;
}

int main() {
  cin >> N;
  repeat(i, N) cin >> X[i] >> Y[i];

  sort(X, X + N);
  sort(Y, Y + N);

  int mid = N / 2;
  long long ans = 0;
  if (N % 2) {
    ans = score(X[mid], Y[mid]);
  } else {
    ans = max(score(X[mid], Y[mid]), score(X[mid - 1], Y[mid - 1]));
  }
  cout << ans << endl;

  return 0;
}