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

int main() {
    int N;
    cin >> N;
    auto G = vectors(0, N, 0);
    repeat(i, N - 1) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    vector<int> C(N);
    repeat(i, N) cin >> C[i];
    sort(rbegin(C), rend(C));
    vector<int> D(N, -1);

    auto dfs = [&](auto f, int cur, int &i) -> int {
        int res = 0;
        D[cur] = C[i++];
        for (int to : G[cur]) {
            if (D[to] != -1) continue;
            res += f(f, to, i);
            res += min(D[cur], D[to]);
        }
        return res;
    };

    int i = 0;
    int M = dfs(dfs, 0, i);
    cout << M << endl;
    repeat(i, N) cout << D[i] << ((i == N - 1) ? '\n' : ' ');
    return 0;
}