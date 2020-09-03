// N桁の短歌数
// 1 ~ 9の数字から二つ選んだ時
// Comb(9,2) * (2^N - 2)
// 0 と 1~9 の数字から二つ選んだ時
// 9 * (2^(N-1) - 1)
// 両方足すと、
// a_N = 81 * (2^(N-1) - 1) ( 1 <= N)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int keta = 0;

#define PRINT(X) cout << #X << " " << X << endl;

void rec(ll N, ll d, string &s) {
    set<int> se;
    for (auto c : s) se.insert(c - '0');
    ll offset = 0;
    if (N == 0) return;
    if (se.size() == 0) {
        for (int i = 1; i <= 9; i++) {
            ll add = 9LL * ((1LL << (keta - (d + 1))) - 1);
            // 短歌数を小さいやつから0-indexedで番号つけたとき
            // offset + addは、先頭の数字をiにしたときの短歌数で一番大きい数の番号
            // 最初のサンプルで、(keta = 2)
            // 先頭一桁目決めるとき、offset = 0, add = 9
            // offset + add = 9番目の短歌数は、10, 11, ..., "19"
            if (offset + add >= N) {
                s += (char)(i + '0');
                rec(N - offset, d + 1, s);
                return;
            }
            offset += add;
        }
    } else if (se.size() == 1) {
        for (int i = 0; i <= 9; i++) {
            if (s[0] - '0' == i) {
                ll add = 9LL * ((1LL << (keta - (d + 1))) - 1);
                if (offset + add >= N) {
                    s += (char)(i + '0');
                    rec(N - offset, d + 1, s);
                    return;
                }
                offset += add;
            } else {  // XX...X Y
                //cerr << "offset: " << offset << " N: " << N << endl;
                ll add = 1LL << (keta - (d + 1));
                if (offset + add >= N) {
                    s += (char)(i + '0');
                    rec(N - offset, d + 1, s);
                    return;
                }
                offset += add;
            }
        }
    } else {
        for (int num : se) {
            ll add = 1LL << (keta - (d + 1));
            if (offset + add >= N) {
                s += (char)(num + '0');
                rec(N - offset, d + 1, s);
                return;
            }
            offset += add;
        }
    }
}

int main() {
    // 初期化
    const int MAX_KETA = 64;
    vector<long long> A(MAX_KETA, 0);
    // A[i] := 0 ~ i桁までの短歌数
    // sum_{i=0}^{N} 81 * (2^(i-1) - 1)
    // 1 + ... + 2^(N-1) = 2^N - 1
    for (int i = 0; i < 64; ++i) {
        A[i] = 81LL * ((1LL << i) - 1 - i);
    }
    //for(auto p : A) cout << p << endl;
    // B[i] := 先頭1桁目が決まって残り(N-1)桁が何通り
    // B[i] := 9 * (2^(N-1) - 1)
    // 先頭二桁目が、一桁目と同じとき、残り(N-2)桁は
    // 2^(N-2) - 1
    // 一桁目と違うとき
    // 2^(N-2)

    long long N;
    while (cin >> N, N) {
        keta = 0;
        while (A[keta] < N) keta++;
        N -= A[keta - 1];
        // cout << "keta: " << keta << endl;
        // cout << "N:" << N << endl;
        string res = "";
        rec(N, 0, res);
        cout << res << endl;
    }

    return 0;
}