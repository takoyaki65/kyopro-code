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
  long long num = 0;
  long long max_time = 0;
  cin >> num >> max_time;
  vector<long long> a_vec(num);
  repeat(i, num) cin >> a_vec[i];
  vector<long long> left_vec, right_vec;
  copy(a_vec.begin(), a_vec.begin() + (num / 2), back_inserter(left_vec));
  copy(a_vec.begin() + (num / 2), a_vec.end(), back_inserter(right_vec));

  vector<long long> left_enum;
  left_enum.reserve((1 << (num / 2)));
  {
    int l_size = left_vec.size();
    for (int bits = 0; bits < (1 << l_size); ++bits) {
      long long sm = 0;
      repeat(i, l_size) {
        if ((bits >> i) & 1) sm += left_vec[i];
      }
      left_enum.push_back(sm);
    }
    sort(left_enum.begin(), left_enum.end());
  }

  long long ans = -1;
  int r_size = right_vec.size();
  for (int bits = 0; bits < (1 << r_size); ++bits) {
    long long sm = 0;
    repeat(i, r_size) {
      if ((bits >> i) & 1) sm += right_vec[i];
    }

    if (sm > max_time) continue;
    long long rest =
        *prev(upper_bound(left_enum.begin(), left_enum.end(), max_time - sm));
    setmax(ans, sm + rest);
  }
  cout << ans << endl;
  return 0;
}