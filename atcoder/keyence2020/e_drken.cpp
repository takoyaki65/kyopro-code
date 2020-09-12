#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using pint = pair<int, int>;
using Graph = vector<vector<pint>>;
const int INF = 1000000000;

int N, M;
Graph G;
vector<int> D;

void solve() {
    map<int, vector<int>> ma;
    for (int v = 0; v < N; ++v) ma[D[v]].push_back(v);

    vector<int> color(N, -1);
    vector<int> res(M, INF);
    for (auto it : ma) {
        int val = it.first;
        auto vs = it.second;
        for (auto v : vs) {
            if (color[v] != -1) continue;
            bool exist = false;
            for (auto e : G[v]) {
                int nv = e.first;
                if (D[v] < D[nv]) continue;
                exist = true;
                res[e.second] = val;
                if (color[nv] == -1) {
                    color[v] = 0;
                    color[nv] = 1;
                } else {
                    color[v] = 1 - color[nv];
                }
                break;
            }
            if (!exist) {
                cout << -1 << endl;
                return;
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        if (color[i] == 0)
            cout << "W";
        else
            cout << "B";
    }
    cout << endl;
    for (int i = 0; i < M; ++i) cout << res[i] << endl;
}

int main() {
    cin >> N >> M;
    D.resize(N);
    for (int i = 0; i < N; ++i) cin >> D[i];
    G.assign(N, vector<pint>());
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u].emplace_back(v, i);
        G[v].emplace_back(u, i);
    }
    solve();
}