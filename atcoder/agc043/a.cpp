#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
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

// (1,1) -> (H, W)までの経路で、黒マスを踏む回数が最小になるものを調べる
// その経路にある黒マスを白マスにするための最小操作回数を調べる
// でも、黒マスを踏む回数が多いやつでも操作回数が小さいやつもあるのでは？
// (1,1) -> (H, W)の経路で、色が白->黒になる回数が最小になる経路を調べる

int main() {
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    repeat(i, H) cin >> S[i];
    auto dp = vectors(1e9, H, W);
    if (S[0][0] == '#')
        dp[0][0] = 1;
    else
        dp[0][0] = 0;
    repeat(i, H) {
        repeat(j, W) {
            //cout << i << " " << j << endl;
            if (i - 1 >= 0) {
                if (S[i - 1][j] == '.' and S[i][j] == '#') {
                    setmin(dp[i][j], dp[i - 1][j] + 1);
                } else {
                    setmin(dp[i][j], dp[i - 1][j]);
                }
            }
            if (j - 1 >= 0) {
                if (S[i][j - 1] == '.' and S[i][j] == '#') {
                    setmin(dp[i][j], dp[i][j - 1] + 1);
                } else {
                    setmin(dp[i][j], dp[i][j - 1]);
                }
            }
        }
    }
    cout << dp[H - 1][W - 1] << endl;
    return 0;
}