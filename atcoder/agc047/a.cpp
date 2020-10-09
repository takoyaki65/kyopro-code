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

int main() {
    int N;
    cin >> N;
    map<pair<int, int>, int> cnt;
    repeat(i, N) {
        double A;
        cin >> A;
        long long x = llround(A * 1e9);
        int div2 = 0, div5 = 0;
        while (x % 2 == 0) {
            x /= 2, ++div2;
        }
        while (x % 5 == 0) {
            x /= 5, ++div5;
        }
        cnt[{div2, div5}]++;
    }
    long long res = 0;
    for (auto p1 : cnt) {
        for (auto p2 : cnt) {
            auto [a25, a] = p1;
            auto [a2, a5] = a25;
            auto [b25, b] = p2;
            auto [b2, b5] = b25;
            if (a2 + b2 < 18 or a5 + b5 < 18) continue;
            if (p1 < p2) {
                res += (long long)a * b;
            } else if (p1 == p2) {
                res += (long long)a * (a - 1) / 2;
            }
        }
    }
    cout << res << endl;
    return 0;
}