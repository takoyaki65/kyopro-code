// 2分木みたいになるらしい
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    sort(A.rbegin(), A.rend());
    long long res = 0LL;
    for (int i = 1; i <= N - 1; ++i) {
        res += A[i / 2];
    }
    cout << res << endl;
    return 0;
}