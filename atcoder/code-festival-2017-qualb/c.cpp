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

int main() {
    int N, M;
    cin >> N >> M;
    auto G = vectors(-1, N, 0);
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        --A, --B;
        G[A].push_back(B);
        G[B].push_back(A);
    }

    vector<int> color(N, -1);
    // 二部グラフか判定
    auto dfs = [&](auto f, int cur, int col) -> bool {
        color[cur] = col;
        for (int next_v : G[cur]) {
            if (color[next_v] == col) return false;

            if (color[next_v] == -1)
                if (!f(f, next_v, 1 - col)) return false;
        }
        return true;
    };

    if (dfs(dfs, 0, 0)) {
        // 二部グラフの場合
        long long B = 0, W = 0;
        for (int col : color) {
            if (col == 1)
                ++B;
            else
                ++W;
        }
        cout << B * W - (long long)M << endl;
    } else {
        // 二部グラフじゃない場合
        long long ans = (long long)N * (N - 1) / 2 - M;
        cout << ans << endl;
    }

    return 0;
}