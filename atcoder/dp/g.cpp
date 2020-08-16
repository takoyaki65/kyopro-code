#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

template <class T>
using P = pair<T, T>;

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

    V<int> L(N, 0);
    priority_queue<P<int>> que;
    for (int i = 0; i < N; ++i) {
        que.emplace(0, i);
    }
    /*
    for (int p : L) cout << p << " ";
    cout << endl;
    */
    while (!que.empty()) {
        int x = que.top().second;
        int l = que.top().first;
        que.pop();
        //cout << "x: " << x << " l: " << l << endl;
        if (L[x] > l) continue;
        for (int t : G[x]) {
            if (L[t] < L[x] + 1) {
                L[t] = L[x] + 1;
                /*
                cout << "que push: "
                     << "x: " << t << " l: " << L[x] + 1 << endl;
                     */
                que.emplace(L[x] + 1, t);
            }
        }
        /*
        for (int p : L) cout << p << " ";
        cout << endl;
        */
    }

    cout << *max_element(L.begin(), L.end()) << endl;
    return 0;
}