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
    auto In = vectors(-1, alphabet, 0);
    auto Out = vectors(-1, alphabet, 0);
    repeat(i, N) {
        In[S[i] - 'a'].push_back(i);
        Out[T[i] - 'a'].push_back(i);
    }

    vector<int> dp(N, 0);
    dp[0] = 1;
    repeat(i, N) {
        // j<iを満たす星jから星iまで行く方法が何通りあるか
        for (int from : In[T[i] - 'a']) {
            if (from >= i) break;
            dp[i] += dp[from];
            dp[i] %= MOD;
        }
    }
    cout << dp[N - 1] << endl;
    return 0;
}