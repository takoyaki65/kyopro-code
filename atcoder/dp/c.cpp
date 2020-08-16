#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

template <class T>
using P = pair<T, T>;

int main() {
    int N;
    cin >> N;
    VV<int> abc(N, V<int>(3));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> abc[i][j];
        }
    }

    VV<int> DP(N + 1, V<int>(3));
    for (int i = 0; i < N; ++i) {
        // i -> i + 1への遷移
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (j == k) continue;
                DP[i + 1][k] = max(DP[i + 1][k], DP[i][j] + abc[i][k]);
            }
        }
    }

    cout << *max_element(DP[N].begin(), DP[N].end()) << endl;
    return 0;
}