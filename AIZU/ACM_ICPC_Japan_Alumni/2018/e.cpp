#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    while (cin >> N >> M, N | M) {
        vector<vector<int>> G(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        vector<int> color(N, -1);
        // https://qiita.com/drken/items/a803d4fc4a727e02f7ba
        auto dfs = [&](auto f, int cur, int col) -> bool {
            color[cur] = col;
            for (int to : G[cur]) {
                if (color[to] != -1) {
                    if (color[to] == col) return false;
                    continue;
                }

                if (!f(f, to, 1 - col)) return false;
            }
            return true;
        };

        // グラフを0と1の二つに分ける
        bool flg = dfs(dfs, 0, 0);

        if (!flg) {
            cout << 0 << endl;
        } else {
            int num0 = 0;
            for (int col : color)
                if (col == 0) ++num0;

            int num1 = N - num0;
            set<int> ans;
            if (num0 % 2 == 0) ans.insert(num0 / 2);
            if (num1 % 2 == 0) ans.insert(num1 / 2);
            cout << ans.size() << endl;
            for (int p : ans) cout << p << endl;
        }
    }
    return 0;
}