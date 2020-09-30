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
#define sz(x) int(x.size())
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

// 上下左右に隣り合う黒白マス間を辺でつないだグラフについて、
// 各連結成分ごとの黒マスと白マスの個数をbi, wiとすると、
// 組合せの個数はbi * wi個
// なぜかwaになる、助けて、、、

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int main() {
    int H, W;
    cin >> H >> W;
    vector<string> s(H);
    repeat(i, H) cin >> s[i];
    auto G = vectors(0, H * W, 0);
    vector<bool> col(H * W);
    repeat(y, H) {
        repeat(x, W) {
            col[W * y + x] = (s[y][x] == '.');
            repeat(i, 4) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (ny < 0 || ny >= H || nx < 0 || nx >= W) continue;
                if (s[ny][nx] != s[y][x]) {
                    int v = W * y + x;
                    int nv = W * ny + nx;
                    G[v].push_back(nv);
                    G[nv].push_back(v);
                }
            }
        }
    }

    vector<bool> visited(H * W, false);
    long long res = 0;
    for (int i = 0; i < H * W; ++i) {
        if (visited[i]) continue;
        long long black = 0, white = 0;
        queue<int> que;
        visited[i] = true;
        que.push(i);
        while (!que.empty()) {
            int v = que.front();
            if (col[v])
                ++white;
            else
                ++black;
            que.pop();
            for (int to : G[v]) {
                if (!visited[to]) {
                    visited[to] = true;
                    que.push(to);
                }
            }
        }
        res += black * white;
    }
    cout << res << endl;
    return 0;
}