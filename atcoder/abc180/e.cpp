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

int main() {
    int N{0};
    cin >> N;
    vector<int> x(N), y(N), z(N);
    repeat(i, N) cin >> x[i] >> y[i] >> z[i];
    auto dist = vectors(0, N, N);
    repeat(i, N) {
        repeat(j, i) {
            dist[i][j] = dist[j][i] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
            dist[i][j] += max(0, z[j] - z[i]);
            dist[j][i] += max(0, z[i] - z[j]);
        }
    }

    auto dp = vectors(-1, N, (1 << N));
    auto rec = [&](auto f, int v, int S) -> int {
        if (dp[v][S] >= 0) {
            return dp[v][S];
        }

        if (S == (1 << N) - 1 and v == 0) {
            return dp[v][S] = 0;
        }

        int res = 1000000007;
        for (int u = 0; u < N; ++u) {
            if (!(S >> u & 1)) {
                setmin(res, f(f, u, S | 1 << u) + dist[v][u]);
            }
        }
        return dp[v][S] = res;
    };

    cout << rec(rec, 0, 0) << endl;
    return 0;
}