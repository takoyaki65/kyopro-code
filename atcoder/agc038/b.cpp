#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <functional>
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

template <typename T>
struct SegmentTree {
   private:
    using Func = function<T(T, T)>;
    int n;
    vector<T> node;
    const T e;
    Func f;

   public:
    SegmentTree(vector<T> v, Func _func, T _e) : f(_func), e(_e) {
        int sz = v.size();
        n = 1;
        while (n < sz) n *= 2;
        node.resize(2 * n - 1, e);

        for (int i = 0; i < sz; ++i) node[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; --i) node[i] = f(node[2 * i + 1], node[2 * i + 2]);
    }

    void set(int x, T val) {
        x += (n - 1);
        node[x] = val;
        while (x > 0) {
            x = (x - 1) / 2;
            node[x] = f(node[2 * x + 1], node[2 * x + 2]);
        }
    }

    T get(int pos) {
        return node[pos + n - 1];
    }

    // [a, b)
    T prod(int a, int b, int k = 0, int l = 0, int r = -1) {
        // 最初に呼び出されたときの対象区間は[0, n)
        if (r < 0) r = n;

        if (r <= a or b <= l) return e;

        if (a <= l and r <= b) return node[k];

        T vl = prod(a, b, 2 * k + 1, l, (l + r) / 2);
        T vr = prod(a, b, 2 * k + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
};

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
    int N, K;
    cin >> N >> K;
    vector<int> P(N);
    repeat(i, N) cin >> P[i];
    SegmentTree<int> Smin(
        P, [](int l, int r) { return min(l, r); }, numeric_limits<int>::max());
    SegmentTree<int> Smax(
        P, [](int l, int r) { return max(l, r); }, numeric_limits<int>::lowest());
    UnionFind uf(N - K + 1);
    int unchange = 0;
    repeat(i, N - K + 1) {
        if (Smin.prod(i, i + K) == P[i] and Smax.prod(i, i + K) == P[i + K - 1]) {
            ++unchange;
        }
    }
    repeat(i, N - K) {
        // [i, i + K) の最小値がP[i]と等しく、
        // [i + 1, i + K + 1)の最大値がP[i+K]と等しいなら
        // [0, K)をソートしたやつと[1, K+1)をソートしたやつは等しい
        assert(i + K <= N and i + K + 1 <= N);
        assert(P[i] == Smax.get(i) and P[i] == Smin.get(i));
        assert(P[i + K] == Smax.get(i + K) and P[i + K] == Smin.get(i + K));
        if (Smin.prod(i, i + K) == P[i] and Smax.prod(i, i + K) == P[i + K - 1]) continue;
        if (Smin.prod(i, i + K) == P[i] and Smax.prod(i + 1, i + K + 1) == P[i + K]) {
            uf.unite(i, i + 1);
            //cout << i << " unite " << i + 1 << endl;
        }
    }

    vector<bool> used(N);
    int res = 0;
    repeat(i, N - K + 1) {
        int par = uf.find(i);
        if (used[par]) continue;
        ++res;
        used[par] = true;
    }

    if (unchange == 0) {
        cout << res << endl;
    } else {
        cout << res - unchange + 1 << endl;
    }
    return 0;
}