#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

const int DAT_SIZE = (1 << 18) - 1;
const int MAX_N = 100010;
const int MAX_Q = MAX_N;

int N, Q;
int A[MAX_N];
char T[MAX_Q];
int L[MAX_Q], R[MAX_Q], X[MAX_Q];

// Data[k] := 節点kに対応する区間に一様に加えられた値
// Datb[k] := 節点kに対応する区間に一様でなく加えられた値
long long Data[DAT_SIZE], Datb[DAT_SIZE];

// [a,b)にxを加算する
// kは節点の番号で、区間[l,r)に対応する
void add(int a, int b, int x, int k, int l, int r) {
    if (a <= l and r <= b) {
        Data[k] += x;
    } else if (l < b and a < r) {
        Datb[k] += (min(b, r) - max(a, l)) * x;
        add(a, b, x, k * 2 + 1, l, (l + r) / 2);
        add(a, b, x, k * 2 + 2, (l + r) / 2, r);
    }
}

// [a,b)の和を計算する
// kは節点の番号で、区間[l,r)に対応する
long long sum(int a, int b, int k, int l, int r) {
    if (b <= l or r <= a) {
        return 0;
    } else if (a <= l and r <= b) {
        return Data[k] * (r - l) + Datb[k];
    } else {
        long long res = (min(b, r) - max(a, l)) * Data[k];
        res += sum(a, b, k * 2 + 1, l, (l + r) / 2);
        res += sum(a, b, k * 2 + 2, (l + r) / 2, r);
        return res;
    }
}

void solve() {
    for (int i = 0; i < N; ++i) {
        add(i, i + 1, A[i], 0, 0, N);
    }

    for (int i = 0; i < Q; ++i) {
        if (T[i] == 'C') {
            add(L[i], R[i] + 1, X[i], 0, 0, N);
        } else {
            cout << sum(L[i], R[i] + 1, 0, 0, N) << endl;
        }
    }
}

int main() {
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < Q; ++i) {
        cin >> T[i];
        if (T[i] == 'Q') {
            cin >> L[i] >> R[i];
            --L[i], --R[i];
        } else {
            cin >> L[i] >> R[i] >> X[i];
            --L[i], --R[i];
        }
    }
    // for (int i = 0; i < Q; ++i) {
    //     cout << T[i] << " " << L[i] << " " << R[i] << " " << X[i] << endl;
    // }
    solve();
    return 0;
}