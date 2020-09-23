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

bool find_contradiction(vector<vector<pair<int, int>>> &G) {
    int N = G.size();

    const int INF = numeric_limits<int>::max();
    vector<int> d(N, INF);

    repeat(s, N) {
        if (d[s] != INF) continue;
        d[s] = 0;
        // sから幅優先探索
        queue<pair<int, int>> que;
        que.emplace(s, 0);
        while (!que.empty()) {
            int v = que.front().first;
            int C = que.front().second;
            que.pop();
            if (d[v] < C) continue;
            for (auto edge : G[v]) {
                int to = edge.first;
                int cost = edge.second;
                if (d[to] == INF) {
                    d[to] = C + cost;
                    que.emplace(to, C + cost);
                } else {
                    if (d[to] != C + cost) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    int N, M;
    cin >> N >> M;

    auto G = vectors(pair<int, int>(0, 0), N, 0);
    repeat(i, M) {
        int L, R, D;
        cin >> L >> R >> D;
        --L, --R;
        G[L].emplace_back(R, D);
        G[R].emplace_back(L, -D);
    }

    if (find_contradiction(G)) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
    }
    return 0;
}