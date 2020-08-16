#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    int res = 0;
    for (int i = 1; i <= N; ++i) {
        int a;
        cin >> a;
        if (i & 1 && a & 1) {
            ++res;
        }
    }
    cout << res << endl;
    return 0;
}