#include <bits/stdc++.h>
using namespace std;
#define repeat(i, n) for (int i = (0); i < (n); ++i)

int main() {
    int N, M;
    while (cin >> N >> M, N | M) {
        vector<int> S(N);
        repeat(i, N) {
            cin >> S[i];
        }

        auto simu = [&](int X) -> bool {
            //assert(X >= S[0]);
            int cnt = 0;
            int cur = 0;
            int level = 1;
            while (S.back() >= level + X) {
                while (cur + 1 < N and S[cur + 1] < level + X and abs(level - S[cur]) > abs(level - S[cur + 1])) {
                    ++cur;
                }

                level += max(1, X - abs(level - S[cur]));
                //cout << "cur: " << cur << endl;
                //cout << "level: " << level << endl;
                ++cnt;
            }
            ++cnt;
            return cnt >= M;
        };

        // 1 + X > S[0]でないと最初の敵は倒せない
        // Xの範囲は[ S[0], infinity )
        // X = S[0]でM回未満の戦闘でクリアできるなら答え無し、-1
        if (!simu(S[0])) {
            cout << -1 << endl;
            continue;
        }

        //cout << "first simu done" << endl;

        int lb = S[0] - 1, ub = 100000000;
        while (ub - lb > 1) {
            int md = lb + (ub - lb) / 2;
            if (simu(md)) {
                lb = md;
            } else {
                ub = md;
            }
        }
        cout << lb << endl;
    }
    return 0;
}