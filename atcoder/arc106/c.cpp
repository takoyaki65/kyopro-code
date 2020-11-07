//#define NDEBUG
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

bool validate(const vector<int> &lvec, const vector<int> &rvec, int m) {
    int n = lvec.size();
    vector<pair<int, int>> takahashi(n), aoki(n);
    repeat(i, n) {
        takahashi[i] = make_pair(rvec[i], lvec[i]);
        aoki[i] = make_pair(lvec[i], rvec[i]);
    }
    sort(takahashi.begin(), takahashi.end());
    sort(aoki.begin(), aoki.end());
    int t = 0, a = 0;
    {
        int bound = numeric_limits<int>::min();
        for (int i = 0; i < n; ++i) {
            auto [r, l] = takahashi[i];
            if (bound <= l) ++t;
            setmax(bound, r);
        }
    }
    {
        int bound = numeric_limits<int>::min();
        for (int i = 0; i < n; ++i) {
            auto [l, r] = aoki[i];
            if (bound <= l) ++a;
            setmax(bound, r);
        }
    }
    return (t - a) == m;
}

int main() {
    int n, m;
    cin >> n >> m;
    if (m < 0) {
        cout << -1 << endl;
        return 0;
    }
    if (n == m) {
        cout << -1 << endl;
        return 0;
    }

    if (n - m <= 1 and n >= 2) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> lvec, rvec;
    lvec.reserve(n);
    rvec.reserve(n);
    if (m == 0) {
        for (int i = 0; i < n; ++i) {
            int l = 1 + 2 * i;
            int r = 2 + 2 * i;
            lvec.push_back(l);
            rvec.push_back(r);
        }
    } else {
        assert(n - (m + 2) >= 0);
        lvec.push_back(1);
        rvec.push_back(2 * m + 4);
        for (int i = 0; i < m + 1; ++i) {
            int l = 2 + 2 * i;
            int r = l + 1;
            assert(r < 2 * m + 4);
            lvec.push_back(l);
            rvec.push_back(r);
        }

        for (int i = 0; i < n - (m + 2); ++i) {
            int l = 2 * m + 5 + 2 * i;
            int r = l + 1;
            lvec.push_back(l);
            rvec.push_back(r);
        }
    }
    /* 
    for (int i = 0; i < n; ++i) {
        cout << lvec[i] << ":" << rvec[i] << endl;
    } 
    */

    assert(lvec.size() == n and rvec.size() == n);
    assert(validate(lvec, rvec, m));

    for (int i = 0; i < n; ++i) {
        cout << lvec[i] << " " << rvec[i] << endl;
    }
    return 0;
}