#include <algorithm>
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

// ei1333
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
    vector<pair<int, int>> xi(N), yi(N);
    repeat(i, N) {
        int x, y;
        cin >> x >> y;
        xi[i] = {x, i};
        yi[i] = {y, i};
    }
    sort(xi.begin(), xi.end());
    sort(yi.begin(), yi.end());
    vector<tuple<int, int, int>> edges;
    repeat_from(i, 1, N) {
        int cost = abs(xi[i].first - xi[i - 1].first);
        edges.push_back(make_tuple(cost, xi[i].second, xi[i - 1].second));
    }
    repeat_from(i, 1, N) {
        int cost = abs(yi[i].first - yi[i - 1].first);
        edges.push_back(make_tuple(cost, yi[i].second, yi[i - 1].second));
    }

    sort(edges.begin(), edges.end());
    UnionFind uf(N);
    long long res = 0;
    for (auto edge : edges) {
        int cost = get<0>(edge);
        int u = get<1>(edge);
        int v = get<2>(edge);
        assert(u < N and v < N);
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            res += cost;
        }
    }
    cout << res << endl;
    return 0;
}