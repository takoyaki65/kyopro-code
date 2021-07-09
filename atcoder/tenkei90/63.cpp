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

int H, W;
int P[9][10010];
int num[80010];

int main() {
  cin >> H >> W;
  repeat(i, H) repeat(j, W) cin >> P[i][j];

  int ans = 0;
  repeat(bit, 1 << H) {
    memset(num, 0, sizeof(num));
    repeat(j, W) {
      bool flag = 0;
      int val = 0;
      repeat(i, H) if ((bit >> i) & 1) {
        val = P[i][j];
        break;
      }
      flag = true;
      repeat(i, H) if ((bit >> i) & 1) {
        if (val != P[i][j]) {
          flag = false;
          break;
        }
      }
      if (flag == true)
        num[val] += 1;
    }
    int A = __builtin_popcount(bit);
    int B = *max_element(num, num + H * W + 1);
    ans = max(ans, A * B);
  }
  cout << ans << endl;
  return 0;
}