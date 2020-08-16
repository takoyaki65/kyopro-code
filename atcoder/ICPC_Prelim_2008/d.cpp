// 重み0の辺とコストがかかる辺のグラフ経路問題かな？
// ただ、ロボットの向きもあるので頂点の数はグリッドの数×4方向になる
// このプログラムでは、
/*
    →x
↓y  * * * * * * 
    * * * * * *
    * * * * * *
*/
// になっているよ。
#include <bits/stdc++.h>
using namespace std;

const int dy[] = {0, 1, 0, -1};
const int dx[] = {1, 0, -1, 0};
int s[40][40];
int G[40][40][4];
int c[4];

using ptupl = pair<int, tuple<int, int, int>>;

int main() {
    int w, h;
    while (cin >> w >> h, w || h) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> s[i][j];
            }
        }
        cin >> c[0] >> c[1] >> c[2] >> c[3];
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                memset(G[i][j], -1, sizeof(G[i][j]));
            }
        }
        priority_queue<ptupl, vector<ptupl>, greater<ptupl>> que;
        que.emplace(0, make_tuple(0, 0, 0));
        while (!que.empty()) {
            auto p = que.top();
            que.pop();
            int d = p.first,
                x = get<0>(p.second),
                y = get<1>(p.second),
                dir = get<2>(p.second);
            if (G[y][x][dir] != -1) continue;
            G[y][x][dir] = d;
            // 命令せずに進ませる場合
            if (s[y][x] != 4) {
                int ndir = (dir + s[y][x] + 4) % 4;
                int nx = x + dx[ndir];
                int ny = y + dy[ndir];
                if (!(nx < 0 || nx >= w || ny < 0 || ny >= h))
                    if (G[ny][nx][ndir] == -1) que.emplace(d, make_tuple(nx, ny, ndir));
            }
            // 直進、または右折左折命令をさせる場合
            for (int i = 0; i < 4; ++i) {
                int ndir = (dir + i + 4) % 4;
                int nx = x + dx[ndir];
                int ny = y + dy[ndir];
                if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
                if (G[ny][nx][ndir] == -1) que.emplace(d + c[i], make_tuple(nx, ny, ndir));
            }
        }

        int res = 1000000000;
        for (int i = 0; i < 4; ++i) {
            if (G[h - 1][w - 1][i] == -1) continue;
            res = min(res, G[h - 1][w - 1][i]);
        }
        cout << res << endl;
    }
    return 0;
}