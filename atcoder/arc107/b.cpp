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
    long long N, K;
    cin >> N >> K;
    long long res = 0;
    for (long long ab = 2; ab <= 2 * N; ++ab) {
        // a + b = ab
        long long ab_upper = min(N, ab - 1);
        long long ab_lower = max(ab - N, 1LL);
        //cout << "ab: " << ab << endl;
        //cout << "ab_upper: " << ab_upper << " ab_lower: " << ab_lower << endl;

        if (ab_upper < ab_lower) continue;
        long long cd = ab - K;
        long long cd_upper = min(N, cd - 1);
        long long cd_lower = max(cd - N, 1LL);
        //cout << "cd: " << cd << endl;
        //cout << "cd_upper: " << cd_upper << " cd_lower: " << cd_lower << endl;

        if (cd_upper < cd_lower) continue;
        long long add = (ab_upper - ab_lower + 1) * (cd_upper - cd_lower + 1);
        //cout << "add: " << add << endl;
        res += add;
    }
    cout << res << endl;
    return 0;
}