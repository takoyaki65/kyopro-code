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

int ch2i[300];
int arr[10];

int main() {
  string s;
  cin >> s;
  ch2i['a'] = 0, ch2i['t'] = 1, ch2i['c'] = 2, ch2i['o'] = 3, ch2i['d'] = 4,
  ch2i['e'] = 5, ch2i['r'] = 6;
  for (int i = 0; i < 7; ++i)
    arr[i] = ch2i[s[i]];

  BIT<int> bit(10);
  int ans = 0;
  for (int i = 0; i < 7; ++i) {
    ans += i - bit.sum(arr[i]);
    bit.add(arr[i], 1);
  }

  cout << ans << endl;
  return 0;
}