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
        string s;
        s.reserve(n + 1);
        cin >> s;
        char ch = 'a';
        int num = 0;
        int cur = 0;
        int res = 0;
        int one = 0;
        while (cur < n) {
            if (s[cur] != ch) {
                ch = s[cur];
                if (num >= 2)
                    ++res;
                else
                    ++one;
                num = 1;
            } else {
                ++num;
            }
            ++cur;
        }
        //cout << "more than two: " << res << " one: " << one << endl;
        res += (one + 1) / 2;
        cout << res << endl;
    }
    return 0;
}