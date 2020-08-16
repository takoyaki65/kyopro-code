#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

template <class T>
using P = pair<T, T>;

int main() {
    int N;
    cin >> N;
    V<double> p(N);
    for (int i = 0; i < N; ++i) {
        cin >> p[i];
    }

    VV<double> dp(N + 1, V<double>(N + 1, 0.0));
    dp[0][0] = 1.0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= N; ++j) {
            dp[i + 1][j] = dp[i][j] * (1.0 - p[i]);
        }
        for (int j = 1; j <= N; ++j) {
            dp[i + 1][j] += dp[i][j - 1] * p[i];
        }
    }
    double res = 0.0;
    for (int i = N / 2; i <= N; ++i) {
        res += dp[N][i];
    }
    cout << res << endl;
    return 0;
}