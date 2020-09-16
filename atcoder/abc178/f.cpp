#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
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

// 同じ数の整数がN+1個以上あると無理
// そうでないならうまくできそう
// 構築方法わからｎ、、

const int MAX_N = 200010;

int main() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    repeat(i, N) cin >> A[i];
    repeat(i, N) cin >> B[i];
    vector<int> cntA(N + 1, 0), cntB(N + 1, 0);

    repeat(i, N) {
        ++cntA[A[i]], ++cntB[B[i]];
    }
    repeat(i, N + 1) {
        if (cntA[i] + cntB[i] > N) {
            cout << "No" << endl;
            return 0;
        }
    }

    // https://scrapbox.io/procon-kirokuyou/ABC178_F_-_Contrast_(600)
    // とにかくスワップする
    // AとBがかぶっているところがM個あるなら、そのなかで違う組同士でBiをスワップする
    // と、M-2個になる。その要領で、M-4, M-6, ..., 1個と減らして最後は
    // 例外処理で減らす
    int R = 0, L = 0;
    repeat(i, N) {
        if (A[i] != B[i]) continue;
        setmax(R, i + 1);
        while (R < N) {
            // A[R] == B[R] かつ B[i] != B[R]なRを探す
            if (A[R] == B[R] && B[i] != B[R]) break;
            ++R;
        }
        if (R < N) {
            swap(B[i], B[R]);
        } else {
            while (L < N) {
                if (A[i] != B[L] && A[L] != B[i]) {
                    swap(B[i], B[L]);
                    ++L;
                    break;
                }
                ++L;
            }
        }
    }

    cout << "Yes" << endl;
    repeat(i, N) cout << B[i] << " ";
    cout << endl;

    return 0;
}