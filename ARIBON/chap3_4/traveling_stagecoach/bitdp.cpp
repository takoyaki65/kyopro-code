#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
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

const int MAX_N = 10;
const int MAX_M = 31;
const int INF = 1e9;
int n, m, a, b;
int t[MAX_N];
int d[MAX_M][MAX_M];

double dp[(1 << MAX_N)][MAX_M];

void solve() {
    repeat(i, (1 << n)) fill(dp[i], dp[i] + m, INF);
    dp[(1 << n) - 1][a - 1] = 0;
    double res = INF;
    for (int S = (1 << n) - 1; S >= 0; --S) {
        res = min(res, dp[S][b - 1]);
        for (int v = 0; v < m; ++v) {
            for (int i = 0; i < n; ++i) {
                if ((S >> i) & 1) {
                    for (int u = 0; u < m; ++u) {
                        if (d[v][u] >= 0) {
                            dp[S & ~(1 << i)][u] = min(dp[S & ~(1 << i)][u], dp[S][v] + (double)d[v][u] / t[i]);
                        }
                    }
                }
            }
        }
    }
    if (res == INF) {
        cout << "Impossible" << endl;
    } else {
        cout << fixed << setprecision(10) << res << endl;
    }
}

int main() {
    int p;
    while (true) {
        cin >> n >> m >> p >> a >> b;
        if (!(n | m | p | a | b)) break;
        repeat(i, m) repeat(j, m) d[i][j] = -1;
        repeat(i, n) cin >> t[i];
        repeat(i, p) {
            int x, y, z;
            cin >> x >> y >> z;
            d[x - 1][y - 1] = d[y - 1][x - 1] = z;
        }
        solve();
    }
    return 0;
}