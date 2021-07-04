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

int main() {
  int a, b;
  cin >> a >> b;
  for (int c1 = 0; c1 <= a && 1 * c1 <= b; ++c1) {
    for (int c2 = 0; c1 + c2 <= a && 1 * c1 + 2 * c2 <= b; ++c2) {
      for (int c3 = 0; c1 + c2 + c3 <= a && 1 * c1 + 2 * c2 + 3 * c3 <= b;
           ++c3) {
        for (int c4 = 0;
             c1 + c2 + c3 + c4 <= a && 1 * c1 + 2 * c2 + 3 * c3 + 4 * c4 <= b;
             ++c4) {
          for (int c5 = 0; c1 + c2 + c3 + c4 + c5 <= a &&
                           1 * c1 + 2 * c2 + 3 * c3 + 4 * c4 + 5 * c5 <= b;
               ++c5) {
            int c6 = a - c1 - c2 - c3 - c4 - c5;
            int sum = 1 * c1 + 2 * c2 + 3 * c3 + 4 * c4 + 5 * c5 + 6 * c6;
            if (sum == b) {
              cout << "Yes" << endl;
              return 0;
            }
          }
        }
      }
    }
  }

  cout << "No" << endl;
  return 0;
}