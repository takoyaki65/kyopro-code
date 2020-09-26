#include <algorithm>
#include <atcoder/dsu>
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
const int INF = (int)1e9;

int main() {
    int N;
    cin >> N;
    vector<tuple<int, int, int>> xyi(N);
    repeat(i, N) {
        int x, y;
        cin >> x >> y;
        xyi[i] = make_tuple(x, y, i);
    }

    sort(xyi.begin(), xyi.end());
    vector<int> res(N);
    dsu d(N);
    // first := y座標のmin, second := 元のインデックス
    set<pair<int, int>> tail;
    for (int i = 0; i < N; ++i) {
        int y = get<1>(xyi[i]);
        int ymin = y;
        int id = get<2>(xyi[i]);
        auto it = tail.upper_bound({y - 1, INF});
        // [tail.begin(), itr)をマージ
        auto ptr = tail.begin();
        while (ptr != it) {
            int py = ptr->first;
            int par = ptr->second;
            setmin(ymin, py);
            d.merge(par, id);
            tail.erase(ptr++);
        }
        tail.emplace(ymin, id);
    }

    for (int i = 0; i < N; ++i) {
        int id = get<2>(xyi[i]);
        res[id] = d.size(id);
    }

    for (int i = 0; i < N; ++i) {
        cout << res[i] << endl;
    }
    return 0;
}