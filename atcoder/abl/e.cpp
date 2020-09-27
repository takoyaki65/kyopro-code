#include <algorithm>
#include <atcoder/math>
#include <atcoder/modint>
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
using mint = modint998244353;

int main() {
    int N, Q;
    cin >> N >> Q;
    auto f = [](int a, int b, int x) -> mint {
        mint res = 0;
        mint p = mint(x).pow(a);
        repeat_from(i, a, b) {
            res += p;
            p *= x;
        }
        return res;
    };
    mint num = f(0, N, 1);
    while (Q--) {
        int L, R, D;
        cin >> L >> R >> D;
        int a = N - R;
        int b = N - L + 1;
    }
    return 0;
}