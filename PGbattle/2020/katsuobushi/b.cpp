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

int main() {
    int N, S;
    cin >> N >> S;
    vector<int> a(100, 0);
    // k個まで決めたとき、暫定で
    // a[0] <= a[1] <= ... a[k-1] <= a[k] = a[k+1] = a[k+2] = ... = a[N]
    // 残り配れる数はr
    // a[k+1], ...a[N]にいくら均等に配るか
    auto rec = [&](auto f, int k, int r) -> void {
        if (k == N - 1) {
            a[k + 1] = a[k] + r;
            for (int i = 1; i <= N; ++i) cout << a[i] << " ";
            cout << endl;
            return;
        }
        for (int i = 0; i <= r / (N - k); ++i) {
            a[k + 1] = a[k] + i;
            f(f, k + 1, r - i * (N - k));
        }
    };

    a[0] = 1;
    rec(rec, 0, S - N);
    return 0;
}