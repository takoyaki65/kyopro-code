#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

template <class T>
using P = pair<T, T>;

const int MOD = 1000000007;

int main() {
    int H, W;
    cin >> H >> W;
    V<string> A(H);
    for (int i = 0; i < H; ++i) {
        cin >> A[i];
    }
    VV<int> dp(H, V<int>(W, 0));
    dp[0][0] = 1;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (A[i][j] == '#') continue;
            if (i - 1 >= 0 && A[i - 1][j] == '.') {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
            if (j - 1 >= 0 && A[i][j - 1] == '.') {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
        }
    }
    cout << dp[H - 1][W - 1] << endl;
    return 0;
}