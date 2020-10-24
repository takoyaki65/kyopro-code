#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
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

const int INF = 1e9;

int main() {
    int N, M;
    cin >> N >> M;
    auto G = vectors(0, N, 0);
    auto invG = vectors(0, N, 0);
    repeat(i, M) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        G[a].push_back(b);
        invG[b].push_back(a);
    }

    vector<int> d(N, -1);
    {
        d[N - 1] = 0;
        queue<int> que;
        que.push(N - 1);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int next_v : invG[v]) {
                if (d[next_v] == -1) {
                    d[next_v] = d[v] + 1;
                    que.push(next_v);
                }
            }
        }
    }
    /* for (int x : d) cout << x << " ";
    cout << endl; */

    if (d[0] == -1) {
        cout << -1 << endl;
        return 0;
    }
    vector<int> prev(N, -1);
    {
        repeat(i, N) sort(begin(G[i]), end(G[i]));
        queue<int> que;
        que.push(0);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int next_v : G[v]) {
                if (d[v] == d[next_v] + 1 and prev[next_v] == -1) {
                    prev[next_v] = v;
                    que.push(next_v);
                }
            }
        }
    }

    vector<int> res = {N - 1};
    int cur = N - 1;
    while (cur != 0) {
        cur = prev[cur];
        if (cur == -1) {
            cout << -1 << endl;
            return 0;
        }
        res.push_back(cur);
    }
    reverse(begin(res), end(res));
    for (int x : res) cout << x + 1 << " ";
    cout << endl;
    return 0;
}