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

// https://www.slideshare.net/hcpc_hokudai/binary-indexed-tree
template <typename T>
struct BIT {
 private:
  vector<T> array;
  const int n;

  T sum_Oneindexed(int i) {
    T s = 0;
    while (i > 0) {
      s += array[i];
      i -= i & -i;  // LSB減算
    }
    return s;
  }

  void add_OneIndexed(int i, T x) {
    while (i <= n) {
      array[i] += x;
      i += i & -i;  // LSB加算
    }
  }

 public:
  BIT(int _n) : array(_n + 1, 0), n(_n) {}

  // [0, i]までの累積和
  T sum(int i) { return sum_Oneindexed(++i); }

  // [i, j]の要素の総和
  T sum(int i, int j) {
    return sum_Oneindexed(++j) - sum_Oneindexed((++i) - 1);
  }

  // i番目に要素xを追加
  void add(int i, T x) { add_OneIndexed(++i, x); }
};

int main() {
  int N;
  cin >> N;
  BIT<int> class1(N), class2(N);
  repeat(i, N) {
    int c, p;
    cin >> c >> p;
    switch (c) {
      case 1:
        class1.add(i, p);
        break;
      case 2:
        class2.add(i, p);
      default:
        break;
    }
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int l, r;
    cin >> l >> r;
    --l, --r;
    cout << class1.sum(l, r) << " " << class2.sum(l, r) << endl;
  }
  return 0;
}