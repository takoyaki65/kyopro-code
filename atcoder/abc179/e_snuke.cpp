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
    long long n, x, m;
    cin >> n >> x >> m;
    vector<int> id(m, -1);
    vector<int> a;
    int len = 0;
    long long tot = 0;
    while (id[x] == -1) {
        a.push_back(x);
        id[x] = len++;
        tot += x;
        x = (x * x) % m;
    }

    // 周期の長さ
    int c = len - id[x];

    long long s = 0;
    for (int i = id[x]; i < len; ++i) s += a[i];

    long long ans = 0;
    if (n <= len) {
        repeat(i, n) ans += a[i];
    } else {
        ans += tot;
        n -= len;
        ans += s * (n / c);
        n %= c;
        repeat(i, n) ans += a[id[x] + i];
    }
    cout << ans << endl;
    return 0;
}