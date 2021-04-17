#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
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

const int MAX_N = 64;
#define OR 0
#define AND 1
int op[MAX_N];
int n;

long long f(int lv) {
  if (lv == 0)
    return 1LL;

  if (op[lv] == AND) {
    return f(lv - 1);
  } else {
    // x_lv = Trueの場合 2^lv通り
    // x_lv = Falseの場合 f(lv-1)通り
    return (1LL << lv) + f(lv - 1);
  }
}

int main() {
  cin >> n;
  repeat(i, n) {
    string s;
    cin >> s;
    if (s == "AND")
      op[i + 1] = AND;
    else
      op[i + 1] = OR;
  }

  cout << f(n) << endl;

  return 0;
}