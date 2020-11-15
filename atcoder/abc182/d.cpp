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
    int n{0};
    cin >> n;
    vector<int> a_vec(n, 0);
    repeat(i, n) cin >> a_vec[i];
    // a_acum[i] := [0, i)までのa_vecの累積和
    vector<long long> a_acum(n + 1, 0LL);
    repeat(i, n) a_acum[i + 1] = a_acum[i] + a_vec[i];
    // acum_max[i] := [0, i)までのa_acumのmax値
    vector<long long> acum_max(n + 1, 0LL);
    repeat(i, n) acum_max[i + 1] = max(acum_max[i], a_acum[i + 1]);
    long long cur = 0;
    long long res = 0;
    for (int i = 0; i <= n; ++i) {
        setmax(res, cur + acum_max[i]);
        cur += a_acum[i];
    }
    cout << res << endl;
    return 0;
}