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
    int n, k, c;
    cin >> n >> k >> c;
    string s;
    cin >> s;
    auto getPositions = [&]() {
        vector<int> res;
        for (int i = 0; i < n && sz(res) < k;) {
            if (s[i] == 'o') {
                res.push_back(i);
                i += c + 1;
            } else {
                ++i;
            }
        }
        return res;
    };
    vector<int> l, r;
    l = getPositions();
    reverse(begin(s), end(s));
    r = getPositions();
    repeat(i, k) r[i] = n - 1 - r[i];
    reverse(begin(s), end(s));

    vector<int> lastL(n + 1, -1);
    repeat(i, k) lastL[l[i] + 1] = i;
    repeat(i, n) {
        if (lastL[i + 1] == -1) lastL[i + 1] = lastL[i];
    }

    vector<int> lastR(n + 1, -1);
    repeat(i, k) lastR[r[i]] = i;
    for (int i = n - 1; i >= 0; --i) {
        if (lastR[i] == -1) lastR[i] = lastR[i + 1];
    }
    repeat(i, n) {
        if (s[i] == 'x') continue;
        int li = lastL[i];
        int ri = lastR[i + 1];
        int cnt = 0;
        if (li != -1) cnt += li + 1;
        if (ri != -1) cnt += ri + 1;
        if (li != -1 && ri != -1 && r[ri] - l[li] <= c) {
            --cnt;
        }
        if (cnt >= k) continue;
        cout << i + 1 << endl;
    }
    return 0;
}