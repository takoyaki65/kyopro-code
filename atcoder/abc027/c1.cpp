#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
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

// xが必ず2倍以上になるので、操作の回数はlog_2(10^18) ~ 60回までしからやない
// とりあえず小さい数でシミュレーションするしか、、

int main() {
    long long N;
    cin >> N;

    for (int k = 1; k <= 63; ++k) {
        if (N == (1LL << k) - 1) {
            cout << "Aoki" << endl;
            return 0;
        }
    }
    cout << "Takahashi" << endl;
    return 0;
}