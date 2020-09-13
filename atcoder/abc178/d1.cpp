#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
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

const long long mod = 1000000007;

int main() {
    int N;
    cin >> N;
    vector<long long> dp(N + 1, 0);
    dp[0] = 1;
    long long res = 0;
    for (int End = N - 2; End > 0; End -= 3) {
        for (int i = 1; i < End; ++i) {
            dp[i] = (dp[i] + dp[i - 1]) % mod;
        }
        res = (res + dp[End - 1]) % mod;
    }
    cout << res << endl;
    return 0;
}