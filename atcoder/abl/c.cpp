#include <algorithm>
#include <atcoder/dsu>
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

int main() {
    int N, M;
    cin >> N >> M;
    dsu uf(N);
    repeat(i, M) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        uf.merge(a, b);
    }

    vector<bool> used(N);
    int s = 0;
    repeat(i, N) {
        if (!used[uf.leader(i)]) {
            ++s;
            used[uf.leader(i)] = true;
        }
    }
    cout << s - 1 << endl;
    return 0;
}