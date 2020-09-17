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
    int depth = 1;
    while (N > (1LL << depth) - 1LL) ++depth;
    if (depth % 2) {
        // takahashi -> 2*x+1
        // aoki -> 2*x
        int turn = 0;
        long long x = 1;
        while (x <= N) {
            if (turn % 2 == 0) {
                x = 2LL * x + 1;
            } else {
                x = 2LL * x;
            }
            ++turn;
        }
        if (turn % 2)
            cout << "Aoki" << endl;
        else
            cout << "Takahashi" << endl;
    } else {
        // takahashi -> 2*x
        // aoki -> 2*x+1
        int turn = 0;
        long long x = 1;
        while (x <= N) {
            if (turn % 2 == 0) {
                x = 2LL * x;
            } else {
                x = 2LL * x + 1;
            }
            ++turn;
        }
        if (turn % 2)
            cout << "Aoki" << endl;
        else
            cout << "Takahashi" << endl;
    }
}