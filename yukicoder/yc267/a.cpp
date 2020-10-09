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

// 60 / 12 = 5
// 1秒 -> 長針 360 / 60 / 60 = 1/10 度 -> 短針 360 / 12 / 60 / 60 = 1/120度

int main() {
    int A, B;
    cin >> A >> B;
    double hour = A * 30.0 + B * 0.5;
    double minute = B * 6;
    if (hour >= 360.0) hour -= 360.0;
    if (minute >= 360.0) minute -= 360.0;
    double d = 0;
    if (hour < minute)
        d = 360.0 - (minute - hour);
    else
        d = hour - minute;
    int res = d * 120.0 / (12.0 - 1.0);
    cout << res << endl;
    return 0;
}