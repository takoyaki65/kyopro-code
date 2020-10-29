#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    int potential = 0;
    bool flg = true;
    for (int i = 0; i < N; ++i) {
        string S;
        cin >> S;
        if (S == "A") {
            ++potential;
        } else {
            --potential;
        }
        if (potential < 0) {
            flg = false;
        }
    }
    if (flg and potential == 0)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}