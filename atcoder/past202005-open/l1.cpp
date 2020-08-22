// https://atcoder.jp/contests/past202005-open/submissions/14188846
// リストを使わずにvectorで対処している。すごい。
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> T;
set<tuple<int, int, int>> S1, S2;

void f(set<tuple<int, int, int>> &s, int t, int i, int j) {
    s.erase({t, i, j});
    for (int k = j + 1; k < T[i].size(); ++k) {
        if (!s.count({T[i][k], i, k}) && T[i][k] != -1) {
            s.insert({T[i][k], i, k});
            break;
        }
    }
}

int main() {
    int N, M;
    cin >> N;
    T.resize(N);
    for (int i = 0, k; i < N && cin >> k; ++i) {
        for (int j = 0, t; j < k && cin >> t; ++j) {
            if (j == 0) S1.insert({t, i, j});
            if (j <= 1) S2.insert({t, i, j});
            T[i].push_back(t);
        }
    }

    cin >> M;
    for (int a; cin >> a;) {
        auto p = (a == 1) ? *rbegin(S1) : *rbegin(S2);
        int t = get<0>(p), i = get<1>(p), j = get<2>(p);
        cout << t << "\n";
        T[i][j] = -1;
        if (S1.count({t, i, j})) f(S1, t, i, j);
        f(S2, t, i, j);
    }
    return 0;
}