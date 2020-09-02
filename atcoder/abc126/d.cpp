#include <algorithm>
#include <cmath>
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

// 隣り合う頂点同士の距離が奇数だったら絶対に同じ色にならない
//

int main() {
    int N;
    cin >> N;
    auto G = vectors(make_pair(0, 0), N, 0);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    // for (int i = 0; i < N; ++i) {
    //     cout << "i: " << i << endl;
    //     for (auto pa : G[i]) {
    //         cout << pa.first << " " << pa.second << endl;
    //     }
    // }

    vector<int> color(N, -1);
    auto dfs = [&](auto f, int cur, int col, int x) -> void {
        color[cur] = col;
        for (auto &elem : G[cur]) {
            int to = elem.first, dx = elem.second;
            if (color[to] == -1) {
                if ((x + dx) % 2 == 0)
                    f(f, to, 1, x + dx);
                else
                    f(f, to, 0, x + dx);
            }
        }
    };
    dfs(dfs, 0, 1, 0);
    for (int col : color) {
        cout << col << endl;
    }
    return 0;
}