#include <algorithm>
#include <iostream>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;
template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T &a, T const &b) {
    if (a > b) a = b;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

// Nが少ないので、とりあえずBFSで調べてみる
// きっと根はそこまで深くないといいけどね、、、
// 残っている数列Tの区間が[a,b]になる状態を通過するゲームの過程で、最も
// 得点が大きいやつを探せばいいのかな？
// あ、これ一回しか繰り返さないのか、なら大丈夫だ

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    vector<int> acum = A;
    for (int i = 2; i < N; i += 2) {
        acum[i] += acum[i - 2];
    }
    for (int i = 3; i < N; i += 2) {
        acum[i] += acum[i - 2];
    }
    int res = -5000000;
    for (int tp = 0; tp < N; ++tp) {
        int ap = -1, aoki = -5000000;
        for (int i = 0; i < N; ++i) {
            if (i == tp) continue;
            int s = tp, t = i;
            if (s > t) swap(s, t);
            // 数列Tの区間は[s, t]
            // 青木のスコアは、a[s+1] + ... + a[t - (t-s+1)%2]
            int score = acum[t - (t - s + 1) % 2] - (s - 1 >= 0 ? acum[s - 1] : 0);
            if (aoki < score) ap = i, aoki = score;
        }
        int i = tp, j = ap;
        if (i > j) swap(i, j);
        // 数列Tの区間は[i,j]
        // 高橋のスコアは、a[i] + ... + a[j - (j - i)%2]
        int takahashi = acum[j - (j - i) % 2] - (i - 2 >= 0 ? acum[i - 2] : 0);
        setmax(res, takahashi);
    }
    cout << res << endl;
    return 0;
}