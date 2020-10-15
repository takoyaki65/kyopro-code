#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T &x) {
    return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool setmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

// トポロジカル順序
vector<int> scc(const vector<vector<int>> &G) {
    int n = G.size();
    if (n == 0) return vector<int>();
    vector<vector<int>> rG(n);
    repeat(i, n) {
        for (int j : G[i]) {
            rG[j].push_back(i);
        }
    }
    /* 
    repeat(i, n) {
        for (int j : rG[i]) {
            cout << i << " -> " << j << endl;
        }
    } */

    vector<bool> used(n);
    vector<int> vs;
    vs.reserve(n);
    vector<int> cmp(n);

    auto dfs = [&](auto f, int v) -> void {
        used[v] = true;
        for (int i = 0; i < G[v].size(); ++i) {
            if (!used[G[v][i]]) f(f, G[v][i]);
        }
        vs.push_back(v);
    };

    auto rdfs = [&](auto f, int v, int k) -> void {
        used[v] = true;
        cmp[v] = k;
        for (int i = 0; i < rG[v].size(); ++i) {
            if (!used[rG[v][i]]) f(f, rG[v][i], k);
        }
    };

    fill(begin(used), end(used), false);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) dfs(dfs, i);
    }
    /* for (int x : vs) cout << x << " : ";
    cout << endl; */
    fill(begin(used), end(used), false);
    int k = 0;
    for (int i = (int)vs.size() - 1; i >= 0; --i) {
        if (!used[vs[i]]) rdfs(rdfs, vs[i], k++);
    }
    return cmp;
}

int main() {
    int N, M;
    cin >> N >> M;
    auto G = vectors(0, N, 0);
    repeat(i, N - 1 + M) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        G[a].push_back(b);
    }

    auto cmp = scc(G);
    /*     for (int x : cmp) {
        cout << x << " ";
    } */
    //cout << endl;
    auto rG = vectors(0, N, 0);
    repeat(i, sz(G)) {
        for (int j : G[i]) {
            rG[j].push_back(i);
        }
    }

    vector<int> res(N);
    for (int i = 0; i < N; ++i) {
        int w = -1;     // iの先祖で最大のトポロジカル順序
        int from = -1;  // その先祖のインデックス
        for (int j : rG[i]) {
            if (w < cmp[j]) {
                w = cmp[j];
                from = j;
            }
        }
        if (cmp[i] > w) {
            res[i] = from + 1;
        }
    }

    repeat(i, N) {
        cout << res[i] << endl;
    }
    return 0;
}