#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
#define sz(x) int(x.size())
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

int main() {
    int N, M;
    cin >> N >> M;
    string S;
    cin >> S;
    /*
    vector<int> dp(N + 1, 0);
    vector<int> dpsum(N + 1, 0);
    dp[0] = 1;
    dpsum[0] = 1;
    for (int i = 1; i <= N; ++i) {
        if (S[i] == '1') continue;
        int ri = i - 1;
        int li = max(1, i - M);
        dp[i] = dpsum[ri] - dpsum[li - 1] > 0;
        dpsum[i] = dpsum[i-1] + dp[i];
    }
    */
    int cur = N;
    vector<int> res;
    while (cur > 0) {
        int to = max(0, cur - M);
        while (S[to] == '1' && to < cur) ++to;
        if (to == cur) {
            cout << -1 << endl;
            return 0;
        }
        res.push_back(cur - to);
        cur = to;
    }
    reverse(res.begin(), res.end());
    for (int x : res) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}