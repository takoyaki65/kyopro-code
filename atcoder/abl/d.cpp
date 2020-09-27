#include <algorithm>
#include <atcoder/segtree>
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

using namespace atcoder;

const int MAX_A = 300005;

int op(int a, int b) {
    return max(a, b);
}

int e() {
    return (int)(0);
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    repeat(i, n) cin >> a[i];
    segtree<int, op, e> dp(MAX_A);
    repeat(i, n) {
        int x = a[i];
        int l = max(0, x - k);
        int r = min(x + k + 1, MAX_A);
        int now = dp.prod(l, r) + 1;
        dp.set(x, now);
    }
    int ans = dp.all_prod();
    cout << ans << endl;
    return 0;
}