// https://onlinejudge.u-aizu.ac.jp/solutions/problem/2741/review/2671463/E869120/C++14
#include <algorithm>
#include <iostream>
using namespace std;

int n, m, a[53], b[53], dp[53][53][53][53][2][4], INF = (1 << 30);

int sum(int ty, int L, int R) {
    int sum = 0;
    if (ty == 1) {
        for (int i = L; i <= R; i++) {
            if (a[i] >= 1) sum += a[i];
        }
    }
    if (ty == 2) {
        for (int i = L; i <= R; i++) {
            if (b[i] >= 1) sum += b[i];
        }
    }
    return sum;
}

int solve(int pos1, int pos2, int a1, int a2, int turn, int pass) {
    if (dp[pos1][pos2][a1][a2][turn][pass] != INF) return dp[pos1][pos2][a1][a2][turn][pass];
    if (pass == 3) return 0;

    int ret = 0;
    if (turn == 0) {
        ret = -INF;
        // カードを置く場合
        if (pos1 <= n) {
            if (a[pos1] == -1)
                ret = max(ret, solve(pos1 + 1, pos2, a1, pos2, turn ^ 1, 0));
            else
                ret = max(ret, solve(pos1 + 1, pos2, a1, a2, turn ^ 1, 0));
        }

        // パスする場合
        ret = max(ret, solve(pos1, pos2, pos1, pos2, turn ^ 1, pass + 1) + sum(1, a1, pos1 - 1) - sum(2, a2, pos2 - 1));
    }
    if (turn == 1) {
        ret = INF;
        // カードを置く場合
        if (pos2 <= m) {
            if (b[pos2] == -1)
                ret = min(ret, solve(pos1, pos2 + 1, pos1, a2, turn ^ 1, 0));
            else
                ret = min(ret, solve(pos1, pos2 + 1, a1, a2, turn ^ 1, 0));
        }

        // パスする場合
        ret = min(ret, solve(pos1, pos2, pos1, pos2, turn ^ 1, pass + 1) + sum(1, a1, pos1 - 1) - sum(2, a2, pos2 - 1));
    }
    dp[pos1][pos2][a1][a2][turn][pass] = ret;
    return ret;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    for (int i = 0; i < 2809; i++) {
        for (int j = 0; j < 2809; j++) {
            for (int k = 0; k < 8; k++) dp[i / 53][i % 53][j / 53][j % 53][k / 4][k % 4] = INF;
        }
    }
    int ret = solve(1, 1, 1, 1, 0, 0);
    cout << ret << endl;
    return 0;
}
