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

// l = 2, r = 5, ai = 100
// p = 100 q = 0

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    repeat(i, n) cin >> a[i];
    long long l = 2, r = 2;
    for (int i = n - 1; i >= 0; --i) {
        long long p = (l + a[i] - 1LL) / a[i] * a[i];
        long long q = r / a[i] * a[i];
        //cout << "p: " << p << " q: " << q << endl;
        if (p > q) {
            cout << -1 << endl;
            return 0;
        }
        l = p;
        r = q + a[i] - 1LL;
    }
    cout << l << " " << r << endl;
    return 0;
}