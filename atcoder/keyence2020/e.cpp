#include <algorithm>
#include <cassert>
#include <cmath>
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

// 木になるようにグラフを構築する必要がある
// 同時に二つの未確定の頂点の配色を確定させるか、すでに確定した頂点から未確定の頂点を確定させるようにすれば、木にできる
// (確定させている頂点同士に辺が張られることはないから)
// Diが小さい値のやつから決める

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> D(N);
    map<int, vector<int>> ma;
    repeat(i, N) {
        cin >> D[i];
        ma[D[i]].push_back(i);
    }
    auto G = vectors(make_pair(0, 0), N, 0);
    repeat(i, M) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u].emplace_back(v, i);
        G[v].emplace_back(u, i);
    }

    vector<int> color(N, -1);
    vector<int> res(M, 1000000000);
    for (auto &it : ma) {
        int d = it.first;
        auto &v_vec = it.second;
        for (int v : v_vec) {
            if (color[v] != -1) continue;
            bool flg = false;
            for (auto e : G[v]) {
                int nv = e.first;
                if (D[v] < D[nv]) continue;
                res[e.second] = d;
                if (color[nv] == -1) {
                    color[v] = 0;
                    color[nv] = 1;
                } else {
                    color[v] = 1 - color[nv];
                }
                flg = true;
                break;
            }
            if (!flg) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    repeat(i, N) {
        if (color[i])
            cout << "W";
        else
            cout << "B";
    }
    cout << endl;
    repeat(i, M) {
        cout << res[i] << endl;
    }
    return 0;
}