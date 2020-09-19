#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
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

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

using pii = pair<int, int>;
using pli = pair<long long, int>;

long long d[310];
const long long INF = 1e18;

long long dijkstra(VV<pii> &G, int s, int g) {
    if (s == g) return 0;
    memset(d, -1, sizeof(d));
    priority_queue<pli, vector<pli>, greater<pli>> que;
    que.emplace(0, s);
    while (!que.empty()) {
        long long dist = que.top().first;
        int v = que.top().second;
        que.pop();
        if (d[v] != -1) continue;
        d[v] = dist;
        if (v == g) return dist;
        for (auto edge : G[v]) {
            int next_v = edge.first;
            int cost = edge.second;
            if (d[next_v] == -1) {
                que.emplace(dist + cost, next_v);
            }
        }
    }
    return INF;
}

// TLEになった

int main() {
    int N, M;
    cin >> N >> M;
    auto G = vectors(make_pair(0, 0), N, 0);
    repeat(i, M) {
        int u, v, l;
        cin >> u >> v >> l;
        --u, --v;
        G[u].emplace_back(v, l);
        G[v].emplace_back(u, l);
    }

    int x = G[0].size();
    int V = N + x - 1;
    auto newG = vectors(make_pair(0, 0), V, 0);
    for (int i = 0; i < x; ++i) {
        int to = G[0][i].first + x - 1;
        assert(to < V);
        int l = G[0][i].second;
        newG[i].emplace_back(to, l);
        newG[to].emplace_back(i, l);
    }
    for (int i = 1; i < G.size(); ++i) {
        for (auto p : G[i]) {
            int from = i + x - 1;
            int to = p.first + x - 1;
            assert(from < V && to < V);
            int l = p.second;
            if (p.first != 0) {
                newG[from].emplace_back(to, l);
                newG[to].emplace_back(from, l);
            }
        }
    }

    // 0, ... , x-1の頂点間の最短経路を調べる
    long long res = INF;
    for (int i = 0; i < x; ++i) {
        for (int j = i + 1; j < x; ++j) {
            setmin(res, dijkstra(newG, i, j));
        }
    }
    if (res == INF) {
        cout << -1 << endl;
    } else {
        cout << res << endl;
    }

    return 0;
}