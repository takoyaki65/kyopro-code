#include <bits/stdc++.h>
using namespace std;
#define repeat(i, n) for (int i = (0); i < (n); ++i)
const int INF = 1e9;

int main() {
    int N, M;
    while (cin >> N >> M, N | M) {
        // auto [maxscore, minscore] = ul[i]
        // maxscore := i番目の人が取りうる最高点数
        // minscore := i番目の人が確実に取れる最低点数
        vector<pair<int, int>> ul(N);
        repeat(_, M) {
            int S, K;
            cin >> S >> K;
            if (K == 1) {
                int c;
                cin >> c;
                ul[c - 1].second += S;
                ul[c - 1].first += S;
            } else {
                repeat(i, K) {
                    int c;
                    cin >> c;
                    ul[c - 1].first += S;
                }
            }
        }
        vector<int> lmin(N + 1, INF), rmin(N + 1, INF);
        // lmin[i] := 区間[0, i)でのul[i].secondの最小値
        // rmin[i] := 区間[i+1, N)でのul[i].secondの最小値
        repeat(i, N) {
            lmin[i + 1] = min(lmin[i], ul[i].second);
        }
        for (int i = N - 1; i - 1 >= 0; --i) {
            rmin[i - 1] = min(rmin[i], ul[i].second);
        }

        int res = -1;
        repeat(i, N) {
            res = max(res, ul[i].first - min(lmin[i], rmin[i]) + 1);
        }
        cout << res << endl;
    }
    return 0;
}