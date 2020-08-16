#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

template <class T>
using P = pair<T, T>;

// 遷移が大変だから、ダイクストラとかして計算量減らしたい
// でも制約的にそんな工夫しなくてもよさそう

int main() {
    int N, K;
    cin >> N >> K;
    V<int> h(N);
    for (int i = 0; i < N; ++i) {
        cin >> h[i];
    }

    V<int> DP(N, -1);
    priority_queue<P<int>, V<P<int>>, greater<P<int>>> que;

    que.emplace(0, 0);

    while (!que.empty()) {
        auto p = que.top();
        que.pop();
        int d = p.first;
        int x = p.second;
        if (DP[x] != -1) continue;
        DP[x] = d;
        for (int t = 1; t <= K; ++t) {
            int nx = x + t;
            if (nx >= N) break;
            if (DP[nx] == -1) {
                que.emplace(d + abs(h[nx] - h[x]), nx);
            }
        }
    }
    cout << DP[N - 1] << endl;
    return 0;
}