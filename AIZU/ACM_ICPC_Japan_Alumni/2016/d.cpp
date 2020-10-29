#include <bits/stdc++.h>
using namespace std;
#define repeat(i, n) for (int i = 0; i < (n); ++i)

int m, n;
int dp[52][52][52][52][2][4];
int a[60], b[60];
int a_acum[60], b_acum[60];
const int INF = (1 << 30);
// dp[i][j][k][l][turn][pass_cnt]

// dp配列を-1で初期化するとTLE
// dp配列をINFで初期化するとAC
// なぜ、、、
int rec(int i, int j, int k, int l, int turn, int pass) {
    if (dp[i][j][k][l][turn][pass] != INF) {
        return dp[i][j][k][l][turn][pass];
    }
    if (pass >= 3) {
        // ゲームセット
        //assert(i == k and j == l);
        return 0;
    }

    int ret = 0;
    if (turn == 0) {
        // プレイヤー1のターン
        ret = -INF;
        // スタックに積む
        if (i < n) {
            if (a[i] == -1)
                ret = max(ret, rec(i + 1, j, k, j, !turn, 0));
            else
                ret = max(ret, rec(i + 1, j, k, l, !turn, 0));
        }
        // パスする
        // 直前にプレイヤー2がスタックに積んだ
        int add = (a_acum[i] - a_acum[k]) - (b_acum[j] - b_acum[l]);
        ret = max(ret, rec(i, j, i, j, !turn, pass + 1) + add);
    } else {
        // プレイヤー2のターン
        ret = INF;
        // スタックに積む
        if (j < m) {
            if (b[j] == -1)
                ret = min(ret, rec(i, j + 1, i, l, !turn, 0));
            else
                ret = min(ret, rec(i, j + 1, k, l, !turn, 0));
        }
        // パスする
        int add = (a_acum[i] - a_acum[k]) - (b_acum[j] - b_acum[l]);
        ret = min(ret, rec(i, j, i, j, !turn, pass + 1) + add);
    }
    dp[i][j][k][l][turn][pass] = ret;
    return ret;
}

int main() {
    cin >> n >> m;
    repeat(i, n + 1) {
        repeat(j, m + 1) {
            repeat(k, n + 1) {
                repeat(l, m + 1) {
                    repeat(turn, 2) {
                        repeat(pass, 4) {
                            dp[i][j][k][l][turn][pass] = INF;
                        }
                    }
                }
            }
        }
    }
    repeat(i, n) cin >> a[i];
    repeat(i, m) cin >> b[i];
    for (int i = 0; i < n; ++i) a_acum[i + 1] = a_acum[i] + (a[i] >= 0 ? a[i] : 0);
    for (int i = 0; i < m; ++i) b_acum[i + 1] = b_acum[i] + (b[i] >= 0 ? b[i] : 0);
    cout << rec(0, 0, 0, 0, 0, 0) << endl;

    return 0;
}