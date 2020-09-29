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

template <class T>
T Ifloor(T a, T b) {
    return a / b;
}

template <class T>
T Iceil(T a, T b) {
    return (a + b - 1) / b;
}

//https://wakabame.hatenablog.com/entry/2020/05/24/031143

int main() {
    int t;
    cin >> t;
    while (t--) {
        map<long long, long long> mp;
        long long N, a, b, c, d;
        cin >> N >> a >> b >> c >> d;
        auto dist = [&](auto f, long long n) -> long long {
            if (n == 0) return 0LL;
            if (n == 1) return d;
            auto itr = mp.find(n);
            if (itr != mp.end()) {
                return itr->second;
            }
            long long res = numeric_limits<long long>::max();
            if (n * d > 0) setmin(res, n * d);
            setmin(res, (n - Ifloor(n, 2LL) * 2LL) * d + f(f, Ifloor(n, 2LL)) + a);
            setmin(res, (Iceil(n, 2LL) * 2LL - n) * d + f(f, Iceil(n, 2LL)) + a);
            setmin(res, (n - Ifloor(n, 3LL) * 3LL) * d + f(f, Ifloor(n, 3LL)) + b);
            setmin(res, (Iceil(n, 3LL) * 3LL - n) * d + f(f, Iceil(n, 3LL)) + b);
            setmin(res, (n - Ifloor(n, 5LL) * 5LL) * d + f(f, Ifloor(n, 5LL)) + c);
            setmin(res, (Iceil(n, 5LL) * 5LL - n) * d + f(f, Iceil(n, 5LL)) + c);
            return mp[n] = res;
        };
        cout << dist(dist, N) << endl;
    }
    return 0;
}