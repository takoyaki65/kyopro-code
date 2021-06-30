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

int n;
char str[25];
vector<string> ans;

void rec(int i, int nLeftParen) {
  if (i == n) {
    if (nLeftParen == 0)
      ans.push_back(str);
    return;
  }

  // i文字目を'('にする
  str[i] = '(';
  rec(i + 1, nLeftParen + 1);
  // i文字目を')'にする
  if (nLeftParen > 0) {
    str[i] = ')';
    rec(i + 1, nLeftParen - 1);
  }
  return;
}

int main() {
  cin >> n;
  str[n] = '\0';
  rec(0, 0);

  sort(ans.begin(), ans.end());
  for (const string& out : ans) {
    cout << out << endl;
  }

  return 0;
}