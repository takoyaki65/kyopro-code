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
    int N, M;
    cin >> N >> M;
    UnionFind uf(N + M);
    repeat(i, N) {
        int K;
        cin >> K;
        while (K--) {
            int L;
            cin >> L;
            --L;
            uf.unite(i, N + L);
        }
    }
    repeat(i, N) {
        if (uf.find(i) != uf.find(0)) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
}