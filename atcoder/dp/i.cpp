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
  vector<double> p(N);
  for (int i = 0; i < N; ++i) {
    cin >> p[i];
  }

  // dp[i+1][j] = [0,i]個のコインまで見て、表がj枚ある確率
  vector<vector<double>> dp(N + 1, vector<double>(N + 1, 0.0));
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
  for (int i = (N + 1) / 2; i <= N; ++i) {
    res += dp[N][i];
  }
  cout << fixed << setprecision(10) << res << endl;
  return 0;
}