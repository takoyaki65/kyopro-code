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

int main() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  repeat(i, n) scanf("%d", &a[i]);

  sort(a.begin(), a.end());
  vector<int> nums(n);
  // nums[i] := [0, i]に含まれる整数の種類数
  nums[0] = 1;
  repeat_from(i, 1, n) nums[i] =
      (a[i - 1] != a[i]) ? nums[i - 1] + 1 : nums[i - 1];

  map<int, int> dict;
  repeat(i, n) dict[a[i]] += 1;

  // debug
  // printf("a: ");
  // repeat(i, n) printf("%d ", a[i]);
  // printf("\n");

  // printf("nums: ");
  // repeat(i, n) printf("%d ", nums[i]);
  // printf("\n");

  // printf("dict: ");
  // for (auto [key, val] : dict) {
  //   printf("{%d: %d} ", key, val);
  // }
  // printf("\n");

  int all_kinds = nums[n - 1];

  repeat(k, n) {
    if (all_kinds <= k) {
      printf("0\n");
      continue;
    }
    auto itr = lower_bound(nums.begin(), nums.end(), all_kinds - k);

    // printf("k=%d, all_kinds-k=%d: %ld\n", k, all_kinds - k, itr -
    // nums.begin());

    if (itr == nums.end()) {
      printf("0\n");
      continue;
    }

    printf("%d\n", dict[a[itr - nums.begin()]]);
  }

  return 0;
}