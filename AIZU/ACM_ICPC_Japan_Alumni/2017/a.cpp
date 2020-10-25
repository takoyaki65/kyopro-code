#include <bits/stdc++.h>
using namespace std;
#define repeat(i, n) for (int i = (0); i < (n); ++i)

int main() {
    int N, M;
    while (cin >> N >> M, N | M) {
        vector<int> res(M);
        repeat(_, N) {
            int d, v;
            cin >> d >> v;
            --d;
            res[d] = max(res[d], v);
        }
        int ans = 0;
        for_each(begin(res), end(res), [&ans](int x) { ans += x; });
        cout << ans << endl;
    }
    return 0;
}