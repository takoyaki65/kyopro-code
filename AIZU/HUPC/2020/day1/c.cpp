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

// N >= 20なら、
// m <= 125000
// また、0と1のどちらかを20個ならべる通りは2^20 = 1048576通り
// 2^20 > mになるので、先頭20個のパターンをすべて調べて、
// 使われていない並びをtの先頭20文字に使って、他は'*'

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> S(M);
    repeat(i, M) cin >> S[i];
    int L = min(20, N);
    vector<bool> used(1 << L);
    for (int i = 0; i < M; ++i) {
        int v = 0;
        for (int j = 0; j < L; ++j) {
            if (S[i][j] == '1') {
                v |= 1 << j;
            }
        }
        used[v] = true;
    }
    int last = -1;
    for (int i = 0; i < (1 << L); ++i) {
        if (used[i]) continue;
        last = i;
    }
    string ans(N, '*');
    for (int i = 0; i < L; ++i) {
        if ((last >> i) & 1) {
            ans[i] = '1';
        } else {
            ans[i] = '0';
        }
    }
    cout << ans << endl;
    return 0;
}