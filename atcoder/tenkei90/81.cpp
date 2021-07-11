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

int N, K;
int S[5011][5011];

int main() {
  cin >> N >> K;
  repeat(i, N) {
    int a, b;
    cin >> a >> b;
    S[a][b] += 1;
  }
  repeat(i, 5002) repeat(j, 5001) S[i][j + 1] += S[i][j];
  repeat(j, 5002) repeat(i, 5001) S[i + 1][j] += S[i][j];

  int ans = 0;
  for (int x = 1; x + K < 5002; ++x) {
    for (int y = 1; y + K < 5002; ++y) {
      ans = max(ans, S[x + K][y + K] - S[x - 1][y + K] - S[x + K][y - 1] +
                         S[x - 1][y - 1]);
    }
  }
  cout << ans << endl;
  return 0;
}