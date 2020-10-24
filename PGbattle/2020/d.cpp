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
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

const long long MOD = 1000000007;

int main() {
    int H, W;
    cin >> H >> W;
    vector<long long> crt(1 << H, 0), nxt(1 << H, 0);
    crt[0] = 1;
    for (int i = W - 1; i >= 0; --i) {
        for (int j = H - 1; j >= 0; --j) {
            for (int used = 0; used < (1 << H); ++used) {
                if ((used >> j & 1)) {
                    nxt[used] = crt[used & ~(1 << j)];
                } else {
                    long long res = 0;
                    // 横向き
                    if (j + 1 < H && !(used >> (j + 1) & 1)) {
                        res += crt[used | 1 << (j + 1)];
                    }
                    // 縦向き
                    if (i + 1 < W) {
                        res += crt[used | 1 << j];
                    }
                    nxt[used] = res % MOD;
                }
            }
            swap(crt, nxt);
        }
    }
    cout << crt[0] << endl;
    return 0;
}