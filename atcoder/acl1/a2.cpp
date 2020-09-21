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

    atcoder::dsu d(N);
    int ymin = int(1e9);
    for (int i = 0; i < N; ++i) {
        if (i > 0) {
            // i と i-1が連結しているか
            if (!(ymin == N - i + 1)) d.merge(i, i - 1);
        }
        int y = get<1>(xyi[i]);
        setmin(ymin, y);
    }

    vector<int> res(N);
    for (int i = 0; i < N; ++i) {
        int id = get<2>(xyi[i]);
        res[id] = d.size(i);
    }

    for (int i = 0; i < N; ++i) {
        cout << res[i] << endl;
    }
    return 0;
}