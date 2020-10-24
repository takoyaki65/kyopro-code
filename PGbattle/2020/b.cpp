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

void solve(int N) {
    string res = to_string((1LL << N));
    cout << res << endl;
    reverse(begin(res), end(res));
    int len = sz(res);
    cout << "len: " << len << " N: " << N << endl;
    if (len <= N) {
        for (int i = 0; i < N - len; ++i) {
            res += '0';
        }
        res += ".0";
    }
    reverse(begin(res), end(res));
    cout << res << endl;
    cout << "test1: " << endl;
    long double x = (1LL << N);
    for (int i = 0; i < N; ++i) x /= 10.0;
    cout << x << endl;
    cout << "test2: " << endl;
    x = 1.0;
    for (int i = 0; i < N; ++i) x *= 1 / 5.0;
    cout << x << endl;
}

int main() {
    int N;
    cin >> N;
    string res = to_string((1LL << N));
    cout << res << endl;
    reverse(begin(res), end(res));
    int len = sz(res);
    cout << "len: " << len << " N: " << N << endl;
    if (len <= N) {
        for (int i = 0; i < N - len; ++i) {
            res += '0';
        }
        res += ".0";
    } else {
        // len > N
        // 実はいらない
        res = res.substr(0, N) + '.' + res.substr(N, len - N);
    }
    reverse(begin(res), end(res));
    cout << res << endl;

    /*     for (int i = 0; i < 60; ++i) {
        solve(i);
    } */
    return 0;
}