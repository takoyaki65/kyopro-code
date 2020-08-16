#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

template <class T>
using P = pair<T, T>;

const int MAX_W = 100010;
long long dp1[MAX_W];
long long dp2[MAX_W];

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
        for (int j = 0; j <= W; ++j) {
            nxt[j] = prev[j];
        }
        for (int j = 0; j <= W; ++j) {
            if (prev[j] != -1 && j + w[i] <= W) {
                nxt[j + w[i]] = max(nxt[j + w[i]], prev[j] + v[i]);
            }
        }
        swap(prev, nxt);
    }

    cout << *max_element(prev, prev + W + 1) << endl;
    return 0;
}