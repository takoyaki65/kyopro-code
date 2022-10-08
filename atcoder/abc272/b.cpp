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

bool graph[101][101];
int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  repeat(i, m) {
    int num;
    scanf("%d", &num);
    vector<int> x(num);
    repeat(j, num) {
      scanf("%d", &x[j]);
      --x[j];
    }
    repeat(j, num) repeat_from(k, j + 1, num) graph[x[j]][x[k]] =
        graph[x[k]][x[j]] = true;
  }

  repeat(i, n) repeat(j, i) if (!graph[i][j]) {
    printf("No\n");
    return 0;
  }
  printf("Yes\n");
  return 0;
}