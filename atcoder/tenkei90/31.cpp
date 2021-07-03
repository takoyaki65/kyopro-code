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

// grundy[w][b]
int grundy[60][1400];

int N;
int W[100005], B[100005];
const int max_grundy = 60 * 1400;
bool memo[max_grundy];

int main() {
  cin >> N;
  repeat(i, N) cin >> W[i];
  repeat(i, N) cin >> B[i];

  // grundy数の計算をする
  grundy[0][0] = grundy[0][1] = 0;
  for (int w = 0; w < 60; ++w) {
    for (int b = 0; b < 1400; ++b) {
      int val = 0;
      memset(memo, true, sizeof(memo));
      // [w, b]から遷移可能な遷移先
      // [w, b] -> [w, b - k]
      for (int k = 1; k <= b / 2; ++k) {
        memo[grundy[w][b - k]] = false;
      }
      // [w, b] -> [w-1, b + w]
      if (w >= 1 && b + w < 1400) {
        memo[grundy[w - 1][b + w]] = false;
      }
      for (int k = 0; k < max_grundy; ++k) {
        if (memo[k]) {
          grundy[w][b] = k;
          break;
        }
      }
    }
  }

  int grundy_number = 0;
  repeat(i, N) { grundy_number ^= grundy[W[i]][B[i]]; }

  if (grundy_number > 0) {
    cout << "First" << endl;
  } else {
    cout << "Second" << endl;
  }

  return 0;
}