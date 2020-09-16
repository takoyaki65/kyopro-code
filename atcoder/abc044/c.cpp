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
    long long res = 0;
    // i枚選んで平均をAにできる通りを調べる
    repeat_from(i, 1, N + 1) {
        auto dp = vectors(0, i + 1, i * A + 1);
        dp[0][0] = 1;
        repeat(j, N) {
            for (int k = i - 1; k >= 0; --k) {
                repeat(l, i * A + 1) {
                    if (l - x[j] >= 0) {
                        dp[k + 1][l] += dp[k][l - x[j]];
                    }
                }
            }
        }
        res += dp[i][i * A];
    }
    cout << res << endl;

    return 0;
}