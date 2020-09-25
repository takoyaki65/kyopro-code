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

// たぶん、(x, y)をマージしていって、グループに分けて、
// そのグループについては、1つAiの数字が決まったらすべてのAiが一意に決まると考えた

int main() {
    int N, M;
    cin >> N >> M;
    UnionFind uf(N);
    repeat(i, M) {
        int x, y, z;
        cin >> x >> y >> z;
        uf.unite(x - 1, y - 1);
    }

    vector<bool> used(N, false);
    int res = 0;
    repeat(i, N) {
        int par = uf.find(i);
        if (used[par]) {
            continue;
        } else {
            used[par] = true;
            ++res;
        }
    }
    cout << res << endl;
    return 0;
}