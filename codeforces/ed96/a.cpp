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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        bool flg = false;
        for (int a = 0; 3 * a <= n; ++a) {
            for (int b = 0; 3 * a + 5 * b <= n; ++b) {
                for (int c = 0; 3 * a + 5 * b + 7 * c <= n; ++c) {
                    if (3 * a + 5 * b + 7 * c == n) {
                        cout << a << " " << b << " " << c << " " << endl;
                        flg = true;
                    }
                    if (flg) break;
                }
                if (flg) break;
            }
            if (flg) break;
        }
        if (!flg) cout << -1 << endl;
    }
    return 0;
}