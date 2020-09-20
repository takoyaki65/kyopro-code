#include <algorithm>
#include <atcoder/all>
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

using namespace atcoder;

int op(int a, int b) {
    return min(a, b);
}

int e() {
    return (int)(1e9);
}

// python3 /mnt/c/users/taku65/documents/ac-library/expander.py f_snuke.cpp
// と打つこと

int main() {
    int n, q;
    cin >> n >> q;

    segtree<int, op, e> tx(n + 1), ty(n + 1);
    tx.set(n, n);
    ty.set(n, n);

    long long ans = (long long)(n - 2) * (long long)(n - 2);
    repeat(qi, q) {
        int typ, i;
        cin >> typ >> i;
        if (typ == 1) {
            int r = tx.prod(i, n + 1);
            //cout << "x : " << i << " -> " << r << endl;
            ans -= r - 2;
            //cerr << r << " " << i << endl;
            ty.set(r, op(ty.get(r), i));
        } else {
            int l = ty.prod(i, n + 1);
            //cout << "y : " << i << " -> " << l << endl;
            ans -= l - 2;
            //cerr << l << " " << i << endl;
            tx.set(l, op(tx.get(l), i));
        }
    }

    cout << ans << endl;
    return 0;
}