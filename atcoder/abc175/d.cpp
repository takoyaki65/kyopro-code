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

// 閉路検出が必要。ダブリングっていう方法は思い出せない、、
const long long INF = 1e17;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> P(N), C(N);
    repeat(i, N) {
        cin >> P[i];
        --P[i];
    }
    repeat(i, N) cin >> C[i];

    vector<int> Loop(N, -1);
    vector<long long> Score(N);
    repeat(i, N) {
        if (Loop[i] != -1) continue;
        int cur = i;
        long long score = 0;
        int loop = 0;
        while (true) {
            cur = P[cur], ++loop;
            score += C[cur];
            if (cur == i) break;
        }

        while (true) {
            Loop[cur] = loop, Score[cur] = score;
            cur = P[cur];
            if (cur == i) break;
        }
    }
    /*
    auto Table = vectors(make_pair(0, 0LL), 30, N);
    repeat(i, 30) {
        if (i == 0) {
            repeat(j, N) {
                Table[i][j].first = P[i];
                Table[i][j].second = C[P[i]];
            }
            continue;
        }

        int prev_to = Table[i - 1][j].first;
        Table[i][j].first = Table[i - 1][prev_to].first;
        Table[i][j].second = Table[i - 1][j].second + Table[i - 1][prev_to].second;
    }
    */
    long long ans = -INF;
    K--;
    repeat(i, N) {
        long long res = C[i];
        if (Score[i] <= 0) {
            long long score = C[i];
            int cur = i;
            int K1 = K;
            while (K1 > 0) {
                cur = P[cur];
                K1--;
                score += C[cur];
                setmax(res, score);
                if (cur == i) break;
            }
        } else {
            long long score = Score[i] * (K / Loop[i]) + C[i];
            long long K1 = K % Loop[i];
            setmax(res, score);
            int cur = i;
            while (K1 > 0) {
                cur = P[cur];
                K1--;
                score += C[cur];
                setmax(res, score);
            }
        }
        setmax(ans, res);
    }
    cout << ans << endl;
    return 0;
}