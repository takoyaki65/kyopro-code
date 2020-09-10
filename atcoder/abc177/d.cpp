#include <algorithm>
#include <cmath>
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

// 連結している頂点の集合について、それらは必ず別々に別れなければならない。

int main() {
    int N, M;
    cin >> N >> M;
    auto G = vectors(0, N, 0);
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        --A, --B;
        G[A].push_back(B);
        G[B].push_back(A);
    }

    vector<bool> visited(N, false);
    stack<int> stk;
    for (int i = 0; i < N; ++i) {
        stk.push(i);
    }
    auto dfs = [&](auto f, int cur, int &num) -> void {
        visited[cur] = true;
        ++num;
        for (int to : G[cur]) {
            if (!visited[to]) f(f, to, num);
        }
    };
    int res = 0;
    while (!stk.empty()) {
        int vertex = stk.top();
        stk.pop();
        if (!visited[vertex]) {
            int tmp = 0;
            dfs(dfs, vertex, tmp);
            setmax(res, tmp);
        }
    }
    cout << res << endl;
    return 0;
}