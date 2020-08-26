#include <algorithm>
#include <iostream>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;
template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T &a, T const &b) {
    if (a > b) a = b;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

// もらうdpで行こう
const long long MOD = 1e9 + 7;

int main() {
    int N;
    string S, T;
    cin >> N >> S >> T;

    const int alphabet = 'z' - 'a' + 1;
    // dp[i][j] := 星0~iの入口jから入れる累計数
    auto dp = vectors(0, N, alphabet);
    dp[0][S[0] - 'a'] = 1;
    repeat_from(i, 1, N) {
        dp[i][S[i] - 'a'] = (dp[i][S[i] - 'a'] + dp[i - 1][T[i] - 'a']) % MOD;
        repeat(j, alphabet) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
        }
    }
    // 星N-2から星N-1の出口と同じタイプの入口に入れる通り
    cout << dp[N - 2][T[N - 1] - 'a'] << endl;
    return 0;
}