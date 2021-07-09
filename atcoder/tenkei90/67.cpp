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

long long t8to10(const string& S) {
  long long ret = 0;
  for (const char& ch : S) {
    ret = ret * 8LL;
    ret += ch - '0';
  }
  return ret;
}

string t10to9(long long S) {
  string ret;
  if (S == 0)
    return "0";
  while (S) {
    ret.push_back(char(S % 9 + '0'));
    S /= 9;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

int main() {
  string N;
  int K;
  cin >> N >> K;

  while (K--) {
    long long N10 = t8to10(N);
    // cout << "N10: " << N10 << endl;
    string N9 = t10to9(N10);
    // cout << "N9: " << N9 << endl;
    for (char& ch : N9) {
      if (ch == '8')
        ch = '5';
    }
    N = N9;
  }

  cout << N << endl;

  return 0;
}