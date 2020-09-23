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

// L -> R に Dの辺
// R -> L に-Dの辺を張って、
// 負、または正のサイクルが存在しないか判定
// O(|V| x |E|)なのでTLE,,,

// 蟻本p95
bool find_negative_loop(vector<vector<pair<int, int>>> &G) {
    int V = G.size();
    vector<int> d(V);
    for (int i = 0; i < V; ++i) {
        for (int v = 0; v < V; ++v) {
            for (auto edge : G[v]) {
                int to = edge.first;
                int cost = edge.second;
                if (d[to] > d[v] + cost) {
                    d[to] = d[v] + cost;
                    if (i == V - 1) return true;
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

    if (find_negative_loop(G)) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
    }
    return 0;
}