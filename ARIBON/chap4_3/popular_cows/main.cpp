#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int MAX_V = 10010;
int V;                  // 頂点数
vector<int> G[MAX_V];   // グラフの隣接リスト表現
vector<int> rG[MAX_V];  // 辺の向きを逆さにしたグラフ
vector<int> vs;         // 帰りがけ順の並び
bool used[MAX_V];       // すでに調べたか
int cmp[MAX_V];         // 属する強連結成分のトポロジカル順序

void add_edge(int from, int to) {
    G[from].push_back(to);
    rG[to].push_back(from);
}

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); ++i) {
        if (!used[G[v][i]]) dfs(G[v][i]);
    }
    vs.push_back(v);
}

void rdfs(int v, int k) {
    used[v] = true;
    cmp[v] = k;
    for (int i = 0; i < rG[v].size(); ++i) {
        if (!used[rG[v][i]]) rdfs(rG[v][i], k);
    }
}

int scc() {
    memset(used, 0, sizeof(used));
    vs.clear();

    for (int v = 0; v < V; ++v) {
        if (!used[v]) dfs(v);
    }

    memset(used, 0, sizeof(used));
    int k = 0;
    for (int i = vs.size() - 1; i >= 0; --i) {
        if (!used[vs[i]]) rdfs(vs[i], k++);
    }
    return k;
}

// 入力
const int MAX_N = 10010;
const int MAX_M = 50010;

int main() {
    int N, M;
    cin >> N >> M;
    V = N;
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        add_edge(A - 1, B - 1);
    }
    int n = scc();

    // 候補となる点の数を調べる
    int u = 0, num = 0;
    for (int v = 0; v < V; ++v) {
        if (cmp[v] == n - 1) {
            u = v;
            num++;
        }
    }

    // すべての点から到達可能かどうか調べる
    memset(used, 0, sizeof(used));
    rdfs(u, 0);
    for (int v = 0; v < V; ++v) {
        if (!used[v]) {
            // この点から到達不可能
            num = 0;
            break;
        }
    }
    printf("%d\n", num);
    return 0;
}