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

    auto res = vectors(0, 0, 0);
    auto dfs = [&](auto f, int x, vector<int> &tmp) -> void {
        tmp.push_back(x);
        if (x > N) {
            res.push_back(tmp);
            tmp.pop_back();
            return;
        }
        f(f, 2 * x, tmp);
        f(f, 2 * x + 1, tmp);
        tmp.pop_back();
    };

    vector<int> tmp;
    dfs(dfs, 1, tmp);
    for (auto &elem : res) {
        for (int i = 0; i < elem.size(); ++i) {
            cout << elem[i] << (i == elem.size() - 1 ? "" : " -> ");
        }
        cout << endl;
    }

    return 0;
}