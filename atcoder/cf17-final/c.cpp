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
    vector<int> D(N);
    repeat(i, N) cin >> D[i];
    vector<int> mp(13);
    repeat(i, N + 1) {
        mp[D[i]]++;
    }
    for (auto x : mp) {
        if (x >= 3) {
            cout << 0 << endl;
            return 0;
        }
    }
    vector<int> E(N + 1);
    int res = 0;
    repeat(bit, (1 << 11)) {
        E.clear();
        assert(E.size() == 0);
        repeat(t, 13) {
            if (mp[t] == 0)
                continue;
            else if (mp[t] == 2) {
                E.push_back(t);
                E.push_back(24 - t);
            } else {
                if ((bit >> t) & 1) {
                    E.push_back(t);
                } else {
                    E.push_back(24 - t);
                }
            }
        }
        int s = 100000;
        repeat(i, N + 1) {
            repeat(j, i) {
                int d = abs(E[i] - E[j]);
                setmin(s, min(d, 24 - d));
            }
        }
        setmax(res, s);
    }
    cout << res << endl;
    return 0;
}