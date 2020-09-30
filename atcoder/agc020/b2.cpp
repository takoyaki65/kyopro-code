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
#define sz(x) int(x.size())
using namespace std;
template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T &a, T const &b) {
    if (a > b) a = b;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    repeat(i, n) cin >> a[i];
    long long inf = 2 + n * 1000000008LL;
    auto simu = [&](long long x) -> long long {
        repeat(i, n) {
            x = x - x % a[i];
            if (x == 0LL) return 0LL;
        }
        return x;
    };

    auto lw = [&]() -> long long {
        long long ng = 0, ok = inf;
        while (abs(ok - ng) > 1) {
            long long mid = ng + (ok - ng) / 2LL;
            if (simu(mid) >= 2)
                ok = mid;
            else
                ng = mid;
        }
        return ok;
    };

    auto up = [&]() -> long long {
        long long ok = 0, ng = inf;
        while (abs(ok - ng) > 1) {
            long long mid = ng + (ok - ng) / 2;
            if (simu(mid) <= 2)
                ok = mid;
            else
                ng = mid;
        }
        return ok;
    };

    long long l = lw(), r = up();
    if (l > r) {
        cout << -1 << endl;
    } else {
        cout << l << " " << r << endl;
    }
    return 0;
}