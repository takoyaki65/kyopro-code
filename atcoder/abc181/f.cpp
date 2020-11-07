#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T &x) {
    return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool setmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

// https://ei1333.github.io/luzhiled/snippets/structure/union-find.html
struct UnionFind {
    vector<int> data;

    UnionFind(int sz) {
        data.assign(sz, -1);
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return (false);
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return (true);
    }

    int find(int k) {
        if (data[k] < 0) return (k);
        return (data[k] = find(data[k]));
    }

    int size(int k) {
        return (-data[find(k)]);
    }
};

int main() {
    int N;
    cin >> N;
    vector<double> x(N), y(N);
    repeat(i, N) {
        cin >> x[i] >> y[i];
    }

    auto dist = vectors(1e18, N, N);
    repeat(i, N) {
        repeat(j, i + 1) {
            if (i == j)
                dist[i][j] = 0.0;
            else {
                dist[i][j] = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
            }
        }
    }

    double ok = 0, ng = 100.000001;
    auto check = [&](double r) -> bool {
        repeat(i, N) {
            if (100.0 - r < y[i] + r and y[i] - r < -100.0 + r) return false;
        }

        UnionFind uf(N + 2);
        repeat(i, N) {
            if (100.0 - r < y[i] + r) {
                uf.unite(N, i);
            }
            if (y[i] - r < -100.0 + r) {
                uf.unite(N + 1, i);
            }
            repeat(j, i) {
                if (uf.find(i) == uf.find(j)) continue;
                if (dist[i][j] <= 4 * r * r) uf.unite(i, j);
            }
        }
        return uf.find(N) != uf.find(N + 1);
    };
    while (abs(ng - ok) > 1e-6) {
        double md = (ng + ok) / 2;
        if (check(md)) {
            ok = md;
        } else {
            ng = md;
        }
    }
    cout << fixed << setprecision(10) << ok << endl;
    return 0;
}