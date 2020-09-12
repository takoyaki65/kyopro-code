#include <algorithm>
#include <cmath>
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

int main() {
    int L, R;
    cin >> L >> R;
    map<int, int> ltbl, rtbl;
    repeat(i, L) {
        int l;
        cin >> l;
        ltbl[l]++;
    }
    repeat(i, R) {
        int r;
        cin >> r;
        rtbl[r]++;
    }

    int res = 0;
    for (auto lp : ltbl) {
        auto itr = rtbl.find(lp.first);
        if (itr != rtbl.end()) {
            res += min(lp.second, itr->second);
        }
    }
    cout << res << endl;
    return 0;
}