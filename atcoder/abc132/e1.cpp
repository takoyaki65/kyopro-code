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

#define NDEBUG

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
    --S, --T;
    auto d = vectors(INF, N, 3);
    queue<pii> que;
    d[S][0] = 0;
    que.emplace(0, 3 * S + 0);
    while (!que.empty()) {
        pii p = que.front();
        int v = p.second / 3;
        int m = p.second - 3 * v;
        que.pop();
        if (p.first > d[v][m]) continue;
        for (int to : G[v]) {
            if (d[to][(m + 1) % 3] > d[v][m] + 1) {
                d[to][(m + 1) % 3] = d[v][m] + 1;
                que.emplace(d[v][m] + 1, 3 * to + (m + 1) % 3);
            }
        }
    }
    int res = d[T][0];
    if (res == INF) {
        cout << -1 << endl;
    } else {
        assert(res % 3 == 0);
        cout << res / 3 << endl;
    }
}