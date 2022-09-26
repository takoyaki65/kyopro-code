#include <bits/stdc++.h>
using namespace std;

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
  // [0, _n)までの区間の配列を扱う
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

int c[300000];
vector<int> cx[300001];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &c[i]);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    cx[0].push_back(x - 1);
    cx[c[i]].push_back(x - 1);
  }
  long long ans = 0;
  BIT<int> ftree(n + 1);
  for (int i = 0; i <= n; ++i) {
    int sz = cx[i].size();
    for (int j = 0; j < sz; ++j) {
      if (i == 0)
        ans += ftree.sum(cx[i][j] + 1, n);
      else
        ans -= ftree.sum(cx[i][j] + 1, n);

      ftree.add(cx[i][j], 1);
    }
    for (int j = 0; j < sz; ++j)
      ftree.add(cx[i][j], -1);
  }
  printf("%lld\n", ans);
  return 0;
}