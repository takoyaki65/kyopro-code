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

int main() {
    int N;
    cin >> N;
    auto C = vectors(-1LL, N, 0);
    repeat(i, N) {
        int M;
        cin >> M;
        C[i].resize(M);
        repeat(j, M) {
            cin >> C[i][j];
        }
        sort(C[i].rbegin(), C[i].rend());
    }

    repeat(i, N) {
        repeat_from(j, 1, C[i].size()) {
            C[i][j] += C[i][j - 1];
        }
    }

    // dp[i][j] := 0 ~ i番目までタクシーの割り当てを決めたとき、
    // 未割当がj台残っているときの最大料金
    // dp[i][j] = max(dp[i][j], dp[i-1][j-k] + C[i-1][k])
    vector<long long> dp1(N + 1, 0), dp2(N + 1, 0);
    dp1[1] = 0;
    dp1[0] = C[0][0];
    repeat_from(i, 1, N) {
        repeat_from(j, 1, i + 1) {
            dp2[j] = dp1[j - 1];
        }
        dp2[0] = 0;
        repeat_from(j, 0, i + 1) {
            for (int k = 0; k + j <= i; ++k) {
                setmax(dp2[j], dp1[j + k] + C[i][k]);
            }
        }
        dp1.swap(dp2);
    }
    cout << *max_element(dp1.begin(), dp1.end()) << endl;
}