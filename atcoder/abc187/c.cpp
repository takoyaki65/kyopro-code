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
inline int sz(T &x) {
  return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T &a, T b) {
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
  int n;
  cin >> n;
  std::vector<string> pure_dict, exc_dict;
  pure_dict.reserve(n);
  exc_dict.reserve(n);
  repeat(i, n) {
    string si;
    cin >> si;
    if (si[0] == '!') {
      string ext_str = si.substr(1, si.size() - 1);
      exc_dict.push_back(ext_str);
    } else {
      pure_dict.push_back(si);
    }
  }
  sort(pure_dict.begin(), pure_dict.end());
  sort(exc_dict.begin(), exc_dict.end());

  auto p_itr = pure_dict.begin();
  auto e_itr = exc_dict.begin();
  while (p_itr != pure_dict.end() && e_itr != exc_dict.end()) {
    while (e_itr != exc_dict.end() && *e_itr < *p_itr) ++e_itr;
    if (*e_itr == *p_itr) {
      cout << *e_itr << endl;
      return 0;
    }
    ++p_itr;
  }
  cout << "satisfiable" << endl;
  return 0;
}