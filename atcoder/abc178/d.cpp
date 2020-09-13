#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;
template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T &a, T const &b) {
    if (a > b) a = b;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

// 小さい数でdpしてみる

int main() {
    int N;
    cin >> N;
    auto dp = vectors(0, N + 1, N + 1);
    // dp[i][j] := i個整数作って、総和がjになる通り
    dp[0][0] = 1;
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <= N; ++j) {
            for (int k = 0; j - k >= 3; ++k) {
                dp[i][j] += dp[i - 1][k];
            }
        }
    }
    cout << endl;
    repeat(i, N + 1) {
        repeat(j, N + 1) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}