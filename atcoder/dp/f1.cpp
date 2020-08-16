#include <bits/stdc++.h>
using namespace std;

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

template <class T>
using P = pair<T, T>;

int main() {
    string S, T;
    cin >> S >> T;
    VV<int> DP(S.size() + 1, V<int>(T.size() + 1, 0));
    VV<P<int>> prev(S.size() + 1, V<P<int>>(T.size() + 1));
    for (int i = 0; i < S.size(); ++i) {
        for (int j = 0; j < T.size(); ++j) {
            int m = DP[i][j];
            if (S[i] == T[j]) {
                DP[i + 1][j + 1] = max(DP[i + 1][j + 1], DP[i][j] + 1);
            }

            DP[i + 1][j + 1] = max(DP[i + 1][j + 1], DP[i][j + 1]);
            DP[i + 1][j + 1] = max(DP[i + 1][j + 1], DP[i + 1][j]);
        }
    }
    // 経路復元
    string res = "";
    int y = S.size(), x = T.size();
    while (y > 0 && x > 0) {
        // (y-1, x) -> (y, x)
        if (DP[y][x] == DP[y - 1][x]) {
            --y;
        }
        // (y,x-1) -> (y,x)
        else if (DP[y][x] == DP[y][x - 1]) {
            --x;
        }
        // (y-1, x-1) -> (y, x)
        else {
            res = S[y - 1] + res;
            --y, --x;
        }
    }
    cout << res << endl;
    return 0;
}