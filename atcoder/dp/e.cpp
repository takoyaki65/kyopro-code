#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

template <class T>
using P = pair<T, T>;

// 重さに対する価値の最大値ではなく、
// 価値に対する重さの最小値を求める。
// 双対法的な？

const int MAX_N = 110;
const int MAX_V = 1010;
const int MAX_NV = MAX_N * MAX_V + 1;
long long dp1[MAX_N * MAX_V + 1], dp2[MAX_N * MAX_V + 1];

int main() {
    int N, W;
    cin >> N >> W;
    V<int> w(N), v(N);
    for (int i = 0; i < N; ++i) {
        cin >> w[i] >> v[i];
    }

    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
    long long *prev = dp1, *nxt = dp2;

    prev[0] = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < MAX_NV; ++j) {
            nxt[j] = prev[j];
        }
        for (int j = 0; j < MAX_NV; ++j) {
            if (prev[j] != -1 && j + v[i] < MAX_NV) {
                if (nxt[j + v[i]] == -1)
                    nxt[j + v[i]] = prev[j] + w[i];
                else
                    nxt[j + v[i]] = min(nxt[j + v[i]], prev[j] + w[i]);
            }
        }
        swap(prev, nxt);
    }

    int res = 0;
    for (int i = MAX_N * MAX_V; i >= 0; --i) {
        if (prev[i] != -1 && prev[i] <= W) {
            res = i;
            break;
        }
    }

    cout << res << endl;
    return 0;
}