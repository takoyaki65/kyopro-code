#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m, n || m) {
        vector<int> T(n), H(m);
        int tarou{0}, hanako{0};
        for (int i = 0; i < n; i++) {
            cin >> T[i];
            tarou += T[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> H[i];
            hanako += H[i];
        }

        long long Sum = 10000000000LL;
        int a = -1, b = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (tarou + H[j] - T[i] == hanako + T[i] - H[j]) {
                    if (T[i] + H[j] < Sum) {
                        a = T[i], b = H[j];
                        Sum = T[i] + H[j];
                    }
                }
            }
        }
        if (a != -1 && b != -1) {
            cout << a << " " << b << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}