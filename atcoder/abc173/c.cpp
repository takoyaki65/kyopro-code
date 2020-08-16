// HとWが少ないので全探索ですね
#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, W, K;
    cin >> H >> W >> K;
    char mass[H][W + 10];
    for (int i = 0; i < H; ++i) {
        cin >> mass[i];
    }
    int ans(0);
    for (int row = 0; row < (1 << H); ++row) {
        for (int col = 0; col < (1 << W); ++col) {
            int res(0);
            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < W; ++j) {
                    if ((row >> i) & 1 ^ 1 && (col >> j) & 1 ^ 1 && mass[i][j] == '#') {
                        ++res;
                    }
                }
            }
            if (res == K) ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}