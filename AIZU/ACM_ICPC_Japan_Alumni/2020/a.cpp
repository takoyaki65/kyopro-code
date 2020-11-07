#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m, n | m) {
        vector<int> a(n), b(m);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < m; ++i) {
            cin >> b[i];
        }
        vector<int> res(10);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                string mul = to_string(a[i] * b[j]);
                for (char digit : mul) {
                    ++res[digit - '0'];
                }
            }
        }
        for (int i = 0; i < 10; ++i) {
            cout << res[i] << (i == 9 ? '\n' : ' ');
        }
    }
    return 0;
}