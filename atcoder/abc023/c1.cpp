#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
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

int main() {
    int R, C, K, N;
    cin >> R >> C >> K >> N;
    vector<int> r(N), c(N);
    repeat(i, N) {
        cin >> r[i] >> c[i];
        --r[i], --c[i];
    }

    map<int, int> row_cnt, col_cnt;
    repeat(i, N) {
        ++row_cnt[r[i]];
        ++col_cnt[c[i]];
    }
    map<int, int> m;
    repeat(i, C) m[col_cnt[i]]++;

    long long ans = 0;
    repeat(i, R) ans += m[K - row_cnt[i]];

    repeat(i, N) {
        long long d = row_cnt[r[i]] + col_cnt[c[i]];
        if (d == K) ans--;
        if (d == K + 1) ans++;
    }

    cout << ans << endl;
    return 0;
}