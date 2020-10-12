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
auto vectors(T a, X x) { return vector<T>(x, a); }

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
    int n;
    string s;
    cin >> n >> s;
    string revS = s;
    reverse(begin(revS), end(revS));
    auto posS = vectors(0, 30, 0);
    auto posT = vectors(0, 30, 0);
    repeat(i, sz(s)) {
        posS[s[i] - 'a'].push_back(i);
        posT[revS[i] - 'a'].push_back(i);
    }
    long long ans = 0;
    vector<int> cnt(30);
    BIT<int> bitree(n + 10);
    repeat(i, sz(revS)) {
        int let = revS[i] - 'a';
        int cur = posS[let][cnt[let]];
        int oldC = cur;
        cur += bitree.sum(cur, n - 1);
        int need = i;
        ans += cur - need;
        bitree.add(oldC, 1);
        cnt[let]++;
    }
    cout << ans << endl;
}