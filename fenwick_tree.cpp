#include <bits/stdc++.h>
using namespace std;

// https://www.slideshare.net/hcpc_hokudai/binary-indexed-tree
template <typename T>
struct BIT {
   private:
    vector<T> array;
    const int n;

   public:
    BIT(int _n) : array(_n + 1, 0), n(_n) {}

    // [0, i]までの累積和
    T sum(int i) {
        ++i;
        T s = 0;
        while (i > 0) {
            s += array[i];
            i -= i & -i;  // LSB減算
        }
        return s;
    }

    // [i, j]の要素の総和
    T sum(int i, int j) {
        ++i, ++j;
        return sum(j) - sum(i - 1);
    }

    // i番目に要素xを追加
    void add(int i, T x) {
        ++i;
        while (i <= n) {
            array[i] += x;
            i += i & -i;  // LSB加算
        }
    }
};
