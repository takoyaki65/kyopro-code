// https://drken1215.hatenablog.com/entry/2020/10/01/021300
#include <bits/stdc++.h>
using namespace std;

bool isheiko(long long dx1, long long dy1, long long dx2, long long dy2) {
    return dx1 * dy2 == dy1 * dx2;
}

bool solve(const vector<long long> &x, const vector<long long> &y) {
    int N = (int)x.size();
    if (N <= 3) return true;
    int k = -1;
    for (int i = 2; i < N; ++i) {
        if (!isheiko(x[i] - x[0], y[i] - y[0], x[1] - x[0], y[1] - y[0])) k = i;
    }
    // 全部一直線にあったらOk
    if (k == -1) return true;

    vector<long long> ax = {x[0], x[1], x[k]}, ay = {y[0], y[1], y[k]};
    for (int iter = 0; iter < 3; ++iter) {
        long long dx = ax[(iter + 2) % 3] - ax[(iter + 1) % 3];
        long long dy = ay[(iter + 2) % 3] - ay[(iter + 1) % 3];
        bool ok = true;
        for (int i = 0; i < N; ++i) {
            if (!isheiko(x[i] - ax[iter], y[i] - ay[iter], dx, dy) &&
                !isheiko(x[i] - ax[(iter + 1) % 3], y[i] - ay[(iter + 1) % 3], dx, dy))
                ok = false;
        }
        if (ok) return true;
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<long long> x(N), y(N);
        for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];
        if (solve(x, y))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}