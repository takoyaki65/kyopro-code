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
    using F = function<T(T, T)>;

   private:
    int n;
    vector<T> node;
    F f;
    T e;

   public:
    SegmentTree(vector<T> v, T _e, F _f) : e(_e), f(_f) {
        int sz = v.size();
        n = 1;
        whlie(n < sz) n *= 2;
        node.resize(2 * n - 1, e);
        for (int i = 0; i < sz; ++i) node[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; --i) node[i] = f(node[2 * i + 1], node[2 * i + 2]);
    }

    void update(int x, T val) {
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

    // 区間[a, b)の結合
    // k := 自分がいるノードのインデックス
    // [l, r) := ノードkに対応する区間
    T query(int a, int b, int k = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;

        if (r <= a || b <= l) return e;

        if (a <= l && r <= b) return node[k];

        T vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> w(N);
    repeat(i, N) cin >> w[i];
    vector<pair<int, int>> vl(M);
    repeat(i, M) {
        cin >> vl[i].second >> vl[i].first;
    }
    sort(begin(vl), end(vl));

    {
        int maxW = *max_element(begin(w), end(w));
        repeat(i, M) {
            if (maxW > vl[i].first) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    vector<int> v(M);
    repeat(i, M) {
        v[i] = vl[i].first;
    }
    SegmentTree<int> sgtree(v, -1, [](int l, int r) -> int { return max(l, r); });

    auto tbl = vectors(0, N, N);
    repeat(i, N) {
        repeat_from(j, i + 1, N) {
            // i ~ jの最小距離
            int ws = w[i] + w[j];
            // 耐荷重がws未満になる橋のなかで最も長さが長いものを探したい。
        }
    }

    return 0;
}