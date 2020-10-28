#include <bits/stdc++.h>
using namespace std;
#define repeat(i, n) for (int i = (0); i < (n); ++i)

// 全探索して規則性を見つけるためのコード
/*
const int N = 20;
int dp[N + 1][N + 1][9];

const int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

int main() {
    queue<tuple<int, int, int>> que;
    memset(dp, -1, sizeof(dp));
    dp[0][0][8] = 0;
    que.emplace(0, 0, 8);
    while (!que.empty()) {
        auto [x, y, z] = que.front();
        que.pop();
        repeat(dir, 8) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 0 or nx > N or ny < 0 or ny > N) continue;
            if (z != 8) {
                int px = x + dx[z];
                int py = y + dy[z];
                if (abs(px - nx) <= 1 and abs(py - ny) <= 1) continue;
            }
            if (dp[ny][nx][dir] == -1) {
                dp[ny][nx][dir] = dp[y][x][z] + 1;
                que.emplace(nx, ny, dir);
            }
        }
    }
    repeat(y, N + 1) {
        repeat(x, N + 1) {
            int ret = 1e9;
            repeat(dir, 9) {
                if (dp[y][x][dir] == -1) continue;
                ret = min(ret, dp[y][x][dir]);
            }
            cout << setw(3) << ret;
        }
        cout << endl;
    }
    return 0;
}
*/

int main() {
    int x, y;
    while (cin >> x >> y) {
        x = abs(x);
        y = abs(y);
        if (x > y) swap(x, y);
        if (x % 2 == 0 and y % 2 == 0) {
            cout << x + y << endl;
        } else if (x == 0 and y == 1) {
            cout << 1 << endl;
        } else if (x == 0 and y % 2 == 1) {
            cout << y + 1 << endl;
        } else {
            cout << x / 2 * 2 + y / 2 * 2 + 1 << endl;
        }
    }
}