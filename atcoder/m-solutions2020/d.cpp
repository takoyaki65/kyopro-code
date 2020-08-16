#include <bits/stdc++.h>
//https://qiita.com/ysuzuki19/items/d89057d65284ba1a16ac
#define debug(var)                  \
    do {                            \
        std::cout << #var << " : "; \
        view(var);                  \
    } while (0)
template <typename T>
void view(T e) { std::cout << e << std::endl; }

template <typename T>
void view(const std::vector<T>& v) {
    for (const auto& e : v) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void view(const std::vector<std::vector<T>>& vv) {
    for (const auto& v : vv) {
        view(v);
    }
}

using namespace std;
//yosupo
template <class T>
using V = vector<T>;
template <class T>
using VV = V<V<T>>;

// 2 <= N <= 80, 100 <= Ai <= 200から、動的計画法だなとわかる。
// あり得る状態として、i日目の取引を始める前の時点で
// (持っている所持金)と(持っている株の枚数)の二通り
// いや、(買った株の枚数)と(売った株の枚数)と(持っている所持金)の三つか?
// 最もお金を増やせるパターンとして、100円の株をありったけ買って、翌日200円になった株をすべて売るパターン
// とすると、二日おきに所持金が高々二倍になる
// だから、持てる所持金の合計は1000×2^40 =... となり、10^{10}は超えそう
// だから、
// DP[n][i][j] := n日目の取引を始める直前の時点でi枚買い、j枚売った時の所持金の最大値
// として、max_{i, j}DP[N][i][j]を答えればOK
// 持てる株の最大数は、10×2^40 = ... いや、無理じゃん

// どうやら、
// ・株を買うときは、必ず全財産をつぎ込む
// ・株を売るときは、必ず持っている株をすべて売る
// の二通りの方法が一番最適となる。

// なので、
// DP[x] := x日目に、株の売却が終了した時点の所持金の最大値
// として、
// DP[i] := max(DP[i-1], DP[j-1]/A_j*A_i + DP[j-1]%A_j ) (1 <= j <= N-1)
// となる

int main() {
    int N;
    cin >> N;
    V<int> A(N, 0);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    V<long long> dp(N + 1, 0LL);
    dp[0] = 1000;
    for (int i = 1; i <= N; ++i) {
        dp[i] = dp[i - 1];
        for (int j = 0; j <= i - 1; ++j) {
            dp[i] = max(dp[i], dp[j] % A[j] + dp[j] / A[j] * A[i - 1]);
        }
    }
    cout << dp[N] << endl;
    return 0;
}