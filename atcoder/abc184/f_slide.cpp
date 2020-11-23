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

vector<long long> partial_sum_enum(const vector<long long> &vec) {
  int num = vec.size();
  vector<long long> ret;
  ret.reserve((1 << num) + 1);
  ret.push_back(0);
  for (const long long &val : vec) {
    int cur_size = ret.size();
    for (int i = 0; i < cur_size; ++i) {
      ret.push_back(ret[i] + val);
    }
  }
  return ret;
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

  auto left_enum = partial_sum_enum(left_vec);
  auto right_enum = partial_sum_enum(right_vec);
  sort(left_enum.begin(), left_enum.end());
  sort(right_enum.rbegin(), right_enum.rend());

  long long ans = -1;
  int r = 0;
  for (int l = 0; l < left_enum.size(); ++l) {
    if (left_enum[l] > max_time) continue;
    while (r < right_enum.size() and left_enum[l] + right_enum[r] > max_time)
      ++r;
    setmax(ans, left_enum[l] + right_enum[r]);
  }
  cout << ans << endl;
  return 0;
}