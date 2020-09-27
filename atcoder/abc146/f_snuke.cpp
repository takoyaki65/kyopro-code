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

const int INF = 1 << 30;

int main() {
    int n, m;
    string s;
    cin >> n >> m >> s;
    vector<int> dp(n + 1, INF);
    dp[n] = 0;
    queue<int> q;
    q.push(0);
    for (int i = n - 1; i >= 0; --i) {
        while (1) {
            if (q.size() == 0) {
                cout << -1 << endl;
                return 0;
            }
            if (q.front() != INF && q.size() <= m) break;
            q.pop();
        }
        if (s[i] == '0') dp[i] = q.front() + 1;
        q.push(dp[i]);
    }

    vector<int> ans;
    int x = 0;
    int rest = dp[0];
    while (x < n) {
        --rest;
        int i = 1;
        while (dp[x + i] != rest) ++i;
        ans.push_back(i);
        x += i;
    }
    repeat(i, sz(ans)) {
        cout << ans[i] << (i == sz(ans) - 1 ? '\n' : ' ');
    }
    return 0;
}