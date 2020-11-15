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

// dp

int main() {
    string n_str;
    cin >> n_str;
    int keta = sz(n_str);
    const int INF = 100000;
    auto dp = vectors(INF, keta + 1, 3);
    dp[0][0] = 0;
    repeat(i, keta) {
        repeat(j, 3) {
            // n_str[i]を消さない
            setmin(dp[i + 1][(j + int(n_str[i] - '0')) % 3], dp[i][j]);
            // n_str[i]を消す
            setmin(dp[i + 1][j], dp[i][j] + 1);
        }
    }

    if (dp[keta][0] >= keta) {
        cout << -1 << endl;
    } else {
        cout << dp[keta][0] << endl;
    }

    return 0;
}