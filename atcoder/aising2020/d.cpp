#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    string X;
    cin >> N >> X;

    int PopCount(0);
    for (int i = 0; i < N; ++i) {
        if (X[i] == '1') ++PopCount;
    }

    vector<int> pMod(N, 1), nMod(N, 1);
    for (int i = N - 2; i >= 0; --i) {
        pMod[i] = (pMod[i + 1] << 1) % (PopCount + 1);
        if (PopCount - 1 > 0) nMod[i] = (nMod[i + 1] << 1) % (PopCount - 1);
    }

    // Xp := X % (PopCount + 1)
    // Xn := X % (PopCount - 1)

    int Xp(0), Xn(0);
    for (int i = 0; i < N; ++i) {
        if (X[i] == '1') {
            (Xp += pMod[i]) %= (PopCount + 1);
            if (PopCount - 1 > 0) (Xn += nMod[i]) %= (PopCount - 1);
        }
    }

    for (int i = 0; i < N; ++i) {
        int ans = 1;
        if (X[i] == '1') {
            if (PopCount - 1 <= 0) {
                cout << 0 << endl;
                continue;
            }
            int res = (Xn - nMod[i] + (PopCount - 1)) % (PopCount - 1);
            // シミュレーション
            while (res != 0) {
                res = res % __builtin_popcount((unsigned int)res);
                ++ans;
            }
        } else {
            int res = (Xp + pMod[i] + (PopCount + 1)) % (PopCount + 1);
            while (res != 0) {
                res = res % __builtin_popcount((unsigned int)res);
                ++ans;
            }
        }
        cout << ans << endl;
    }

    return 0;
}