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

// NとAが少ないから枝狩り全探索かな
// 枝狩りだからdpだな

int main() {
    int N, A;
    cin >> N >> A;
    vector<int> x(N);
    repeat(i, N) cin >> x[i];
    auto dp = vectors(0LL, N + 1, N * A + 1);
    dp[0][0] = 1;
    for (int xi : x) {
        for (int i = N - 1; i >= 0; --i) {
            repeat(j, N * A + 1) {
                if (j - xi >= 0) {
                    dp[i + 1][j] += dp[i][j - xi];
                }
            }
        }
    }

    // 1枚,2枚、...選んだ時に平均がAになる通りを足していく
    long long res = 0;
    repeat_from(i, 1, N + 1) {
        res += dp[i][i * A];
    }
    cout << res << endl;
    return 0;
}