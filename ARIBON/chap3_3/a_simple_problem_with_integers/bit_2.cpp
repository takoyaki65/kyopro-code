#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
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

int main() {
    int N, Q;
    cin >> N >> Q;
    BIT<long long> bit0(N), bit1(N);
    repeat(i, N) {
        int A;
        cin >> A;
        bit0.add(i, A);
    }
    while (Q--) {
        char T;
        long long l, r, x;
        cin >> T;
        if (T == 'Q') {
            cin >> l >> r;
            --l, --r;
            long long sr = bit1.sum(r) * r + bit0.sum(r);
            long long sl = bit1.sum(l - 1) * (l - 1) + bit0.sum(l - 1);
            cout << sr - sl << endl;
        } else {
            cin >> l >> r >> x;
            --l, --r;
            bit0.add(l, -x * (l - 1));
            bit0.add(r + 1, x * r);
            bit1.add(l, x);
            bit1.add(r + 1, -x);
        }
    }
    return 0;
}