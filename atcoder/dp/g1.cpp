#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

template <class T>
using P = pair<T, T>;

// 有向閉路が無いので、必ず終点がある？
// だから、終点まで行って、そこから逆にたどればいい
// 再帰でなんとかする

int rec(int v, V<int> &L, VV<int> &G) {
    if (L[v] != -1) return L[v];
    int maxL = 0;
    for (int t : G[v]) {
        maxL = max(maxL, rec(t, L, G) + 1);
    }
    return L[v] = maxL;
}

int main() {
    int N, M;
    cin >> N >> M;
    VV<int> G(N);
    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        G[x].push_back(y);
    }
    V<int> L(N, -1);

    int res = 0;
    for (int i = 0; i < N; ++i) {
        res = max(res, rec(i, L, G));
    }
    cout << res << endl;
    return 0;
}