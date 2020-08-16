#include <bits/stdc++.h>
using namespace std;

int main() {
    string S;
    cin >> S;
    int n = S.size();
    vector<int> RtoL(n, 0), LtoR(n, 0);

    for (int i = 0; i < n; i++) {
        RtoL[i] = LtoR[i] = i;
    }

    for (int i = n - 1; i >= 0; --i) {
        if (S[i] == 'R') {
            RtoL[i] = RtoL[i + 1];
        }
    }

    for (int i = 0; i < n; i++) {
        if (S[i] == 'L') {
            LtoR[i] = LtoR[i - 1];
        }
    }

    vector<int> res(n, 0);
    for (int i = 0; i < n; i++) {
        if (S[i] == 'L') {
            ++res[LtoR[i] + ((i - LtoR[i]) % 2 == 1 ? 1 : 0)];
        } else {
            ++res[RtoL[i] - ((RtoL[i] - i) % 2 == 1 ? 1 : 0)];
        }
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << (i == n - 1 ? '\n' : ' ');
    }

    return 0;
}