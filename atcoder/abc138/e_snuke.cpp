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
    string s, t;
    cin >> s >> t;
    int n = sz(s), m = sz(t);
    vector<vector<int>> is(26);
    repeat(i, n) is[s[i] - 'a'].push_back(i);
    repeat(i, n) is[s[i] - 'a'].push_back(i + n);

    long long ans = 0;
    int p = 0;
    repeat(i, m) {
        int c = t[i] - 'a';
        if (sz(is[c]) == 0) {
            cout << -1 << endl;
            return 0;
        }
        p = *lower_bound(is[c].begin(), is[c].end(), p) + 1;
        if (p >= n) {
            p -= n;
            ans += n;
        }
    }
    ans += p;
    cout << ans << endl;

    return 0;
}