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

int main() {
    string s, g;
    cin >> s >> g;
    int n;
    cin >> n;
    vector<string> vs(n + 2);
    repeat_from(i, 1, n + 1) cin >> vs[i];
    int len = sz(s);
    vs[0] = s;
    vs[n + 1] = g;
    auto G = vectors(INF, n + 2, 0);
    repeat(i, n + 2) G[i].push_back(i);
    repeat(i, n + 2) {
        repeat_from(j, 0, i) {
            if (vs[i] == vs[j]) {
                G[i].push_back(j);
                G[j].push_back(i);
            } else {
                int diff = 0;
                repeat(k, len) {
                    if (vs[i][k] != vs[j][k]) ++diff;
                }
                if (diff == 1) {
                    G[i].push_back(j);
                    G[j].push_back(i);
                }
            }
        }
    }

    // 0 -> nまでの最短距離
    auto dist = vectors(make_pair(INF, -1), n + 2);
    dist[0] = make_pair(0, 0);
    queue<pair<int, int>> que;
    que.emplace(0, 0);
    while (!que.empty()) {
        int d = que.front().first;
        int v = que.front().second;
        que.pop();
        if (d > dist[v].first) continue;
        for (int to : G[v]) {
            if (dist[to].first > dist[v].first + 1) {
                dist[to].first = dist[v].first + 1;
                dist[to].second = v;
                que.emplace(dist[v].first + 1, to);
            }
        }
    }

    vector<int> route;
    route.push_back(n + 1);
    while (route.back() != 0) {
        int to = dist[route.back()].second;
        if (to == -1) {
            cout << -1 << endl;
            return 0;
        }
        route.push_back(to);
    }

    reverse(route.begin(), route.end());
    cout << sz(route) - 2 << endl;
    repeat(i, sz(route)) {
        cout << vs[route[i]] << endl;
    }
    return 0;
}