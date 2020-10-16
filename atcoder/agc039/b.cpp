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

const int INF = 1e9;

int main() {
    int N;
    cin >> N;
    vector<string> G(N);
    repeat(i, N) cin >> G[i];
    vector<int> color(N, -1);
    // https://qiita.com/drken/items/a803d4fc4a727e02f7ba#4-3-%E4%BA%8C%E9%83%A8%E3%82%B0%E3%83%A9%E3%83%95%E5%88%A4%E5%AE%9A
    auto dfs = [&](auto f, int cur, int col) -> bool {
        color[cur] = col;
        repeat(to, N) {
            if (G[cur][to] != '1') continue;
            if (color[to] != -1) {
                if (color[to] == color[cur]) return false;
                continue;
            }
            if (!f(f, to, 1 - col)) return false;
        }
        return true;
    };
    if (!dfs(dfs, 0, 0)) {
        cout << -1 << endl;
        return 0;
    }
    auto d = vectors(INF, N, N);
    repeat(i, N) {
        repeat(j, N) {
            if (G[i][j] == '1') d[i][j] = 1;
        }
    }
    repeat(i, N) d[i][i] = 0;
    repeat(k, N) {
        repeat(i, N) {
            repeat(j, N) {
                setmin(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    int res = -1;
    repeat(i, N) {
        repeat(j, N) {
            if (d[i][j] != INF) {
                setmax(res, d[i][j]);
            }
        }
    }
    cout << res + 1 << endl;
    return 0;
}