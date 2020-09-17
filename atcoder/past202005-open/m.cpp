#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
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

// 頂点{t_i}のグラフを構築しなおして、
// 巡回セールスマン問題をbitDPで解く

const int MAX_N = 100010;
int len[MAX_N];
using pii = pair<int, int>;
const int INF = 1e9 + 7;

int dijkstra(vector<vector<int>> &G, int s, int g) {
    if (s == g) return 0;
    memset(len, -1, sizeof(len));
    priority_queue<pii, vector<pii>, greater<pii>> que;
    len[s] = 0;
    que.emplace(0, s);
    while (!que.empty()) {
        int d = que.top().first;
        int v = que.top().second;
        que.pop();
        //cout << "d : " << d << " v: " << v << endl;
        for (int next_v : G[v]) {
            if (len[next_v] == -1) {
                len[next_v] = d + 1;
                if (next_v == g) return d + 1;
                que.emplace(d + 1, next_v);
            }
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    auto G = vectors(0, N, 0);
    repeat(i, M) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int s, K;
    cin >> s >> K;
    --s;
    vector<int> t(K + 1);
    t[0] = s;
    repeat_from(i, 1, K + 1) {
        cin >> t[i];
        --t[i];
    }
    //cout << "入力完了" << endl;

    int T = K + 1;
    auto newG = vectors(INF, T, T);
    repeat(i, T) {
        repeat_from(j, i + 1, T) {
            int d = dijkstra(G, t[i], t[j]);
            //cout << t[i] << " -> " << t[j] << " : " << d << endl;
            newG[i][j] = d;
            newG[j][i] = d;
        }
    }
    //cout << "graphgen comp" << endl;

    // スタート地点0から、頂点1, 2, 3,... をすべて一回ずつ見る
    auto dp = vectors(-1, (1 << T), T);
    auto rec = [&](auto f, int S, int v) -> int {
        if (dp[S][v] >= 0) {
            return dp[S][v];
        }

        if (S == (1 << T) - 1) {
            return dp[S][v] = 0;
        }

        int res = INF;
        for (int u = 0; u < T; ++u) {
            if (!(S >> u & 1)) {
                setmin(res, f(f, S | (1 << u), u) + newG[v][u]);
            }
        }
        return dp[S][v] = res;
    };

    int res = rec(rec, 1, 0);
    cout << res << endl;

    return 0;
}