#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int main() {
    int N, K;
    string S;
    cin >> N >> K >> S;

    vector<pii> LR;  // [L, R)
    LR.emplace_back(0, 0);
    for (int i = 0; i < N; i++) {
        if (S[i] == '1') {
            int j = i;
            while (S[j] == '1') ++j;
            LR.emplace_back(i, j);
            i = j - 1;
        }
    }
    LR.emplace_back(N, N);

    //for (auto p : LR) cout << p.first << " " << p.second << endl;
    // 尺取り
    int res = 0;
    int r = 0;
    for (int l = 0; l < LR.size(); l++) {
        while (r < LR.size() && r - l <= K) ++r;
        res = max(res, LR[r - 1].second - LR[l].first);
    }
    cout << res << endl;
    return 0;
}