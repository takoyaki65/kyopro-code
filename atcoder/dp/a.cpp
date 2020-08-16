#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

int main() {
    int N;
    cin >> N;
    V<int> h(N);
    for (int i = 0; i < N; ++i) {
        cin >> h[i];
    }
    V<int> DP(N, -1);
    DP[0] = 0;

    for (int i = 0; i < N; ++i) {
        if (i + 1 < N) {
            // i ->i + 1への遷移
            if (DP[i + 1] == -1)
                DP[i + 1] = DP[i] + abs(h[i + 1] - h[i]);
            else
                DP[i + 1] = min(DP[i + 1], DP[i] + abs(h[i + 1] - h[i]));
        }
        if (i + 2 < N) {
            //i -> i + 2への遷移
            if (DP[i + 2] == -1)
                DP[i + 2] = DP[i] + abs(h[i + 2] - h[i]);
            else
                DP[i + 2] = min(DP[i + 2], DP[i] + abs(h[i + 2] - h[i]));
        }
    }
    cout << DP[N - 1] << endl;
    return 0;
}