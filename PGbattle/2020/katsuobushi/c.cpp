#include <algorithm>
#include <atcoder/modint>
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

// 何をしているのかよくわかってない
// https://products.sint.co.jp/hubfs/resource/topsic/pgb2020/code.pdf
using mint = atcoder::modint1000000007;
using pll = pair<long long, long long>;

int main() {
    long long N, M, D;
    long long a[200010];
    cin >> N >> M >> D;
    N--;
    repeat(i, M) {
        cin >> a[i];
        --a[i];
    }
    cout << "input done" << endl;

    auto f = [N, M, D](long long r) -> long long {
        // x%D == r かつ x > Nを満たす最小のxを返す
        long long ret = N / D * D + r;
        if (ret <= N) ret += D;
        return ret;
    };

    // 番兵
    a[M++] = -D;
    a[M++] = f(D - 1);

    auto cmp = [&](long long p, long long q) -> bool {
        if (p % D < q % D) return false;
        if (p % D > q % D) return true;
        if (p / D < q / D) return false;
        return true;
    };
    sort(a, a + M, cmp);
    cout << "sort done " << endl;
    for_each(a, a + M, [](long long x) { cout << x << " "; });
    cout << endl;

    mint ans = 0;
    for (int i = 0; i < M - 1; ++i) {
        long long x = a[i] % D, y = a[i + 1] % D;
        if (x == y) {
            mint cnt = ((a[i + 1] - a[i]) / D - 1);
            ans += cnt * (cnt + 1) / 2;
        } else {
            mint cnt = 0;
            // x
            cnt = ((f(x) - a[i]) / D - 1);
            ans += cnt * (cnt + 1) / 2;
            // y;
            long long r = N % D;
            cnt = ((f(r) - (r - D)) / D - 1);
            if (y - 1 <= r) {
                ans += cnt * (cnt + 1) / 2 * (y - x + 1);
            } else if (r <= x) {
                cnt--;
                ans += cnt * (cnt + 1) / 2 * (y - x - 1);
            } else {
                ans += cnt * (cnt + 1) / 2 * (r - x);
                cnt--;
                ans += cnt * (cnt + 1) / 2 * (y - r - 1);
            }
        }
    }
    cout << ans.val() << endl;
    return 0;
}