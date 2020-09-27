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

const int INF = 1e9 + 7;
using pii = pair<int, int>;

// 「今いる頂点からちょうど3回の移動で行ける頂点」でグラフを構築しなすのは？
int dijkstra(vector<vector<int>> &G, int s, int g) {
    if (s == g) return 0;
    int N = G.size();
    vector<int> d(N, INF);
    priority_queue<pii, vector<pii>, greater<pii>> que;
    d[s] = 0;
    que.emplace(0, s);
    while (!que.empty()) {
        pii p = que.top();
        int v = p.second;
        que.pop();
        if (p.first > d[v]) continue;
        for (int to : G[v]) {
            if (d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                que.emplace(d[v] + 1, to);
            }
        }
    }
    return d[g];
}

int main() {
    int N, M;
    cin >> N >> M;
    auto G = vectors(0, N, 0);
    repeat(i, M) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
    }
    int S, T;
    cin >> S >> T;
    auto newG = vectors(0, N, 0);
    repeat(v, N) {
        set<int> visited;
        auto rec = [&](auto f, int cur, int turn) -> void {
            if (turn >= 3) {
                visited.insert(cur);
                return;
            }
            for (int to : G[cur]) {
                f(f, to, turn + 1);
            }
        };
        rec(rec, v, 0);
        //cout << v + 1 << " -> ";
        for (int to : visited) {
            //cout << to + 1 << " ";
            if (to != v) {
                newG[v].push_back(to);
            }
        }
        //cout << endl;
    }

    int res = dijkstra(newG, S - 1, T - 1);
    if (res == INF) {
        cout << -1 << endl;
    } else {
        cout << res << endl;
    }
    return 0;
}