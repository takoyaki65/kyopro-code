#include <bits/stdc++.h>
using namespace std;

const int MAX_M = 17;
const int MAX_N = 17;
bool color[MAX_N][MAX_M];
int dp[2][1 << MAX_M];

int n, m;

void solve() {
    int *crt = dp[0], *next = dp[1];
    crt[0] = 1;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            for (int used = 0; used < (1 << m); ++used) {
                if ((used >> j & 1) || color[i][j]) {
                    // i, jにはブロックを置く必要がない
                    next[used] = crt[used & ~(1 << j)];
                } else {
                    // 2通りの向きを試す
                    int res = 0;
                    // 横向き
                    if (j + 1 < m && !(used >> (j + 1) & 1) && !color[i][j + 1]) {
                        res += crt[used | 1 << (j + 1)];
                    }
                    // 縦向き
                    if (i + 1 < n && !color[i + 1][j]) {
                        res += crt[used | 1 << j];
                    }
                    next[used] = res % m;
                }
            }
            swap(crt, next);
        }
    }
    printf("%d\n", crt[0]);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            if (x)
                color[i][j] = true;
            else
                color[i][j] = false;
        }
    }
    solve();
}