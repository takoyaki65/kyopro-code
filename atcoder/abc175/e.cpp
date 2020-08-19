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
    int R, C, K;
    cin >> R >> C >> K;
    auto grid = vectors(-1, R, C);
    repeat(i, K) {
        int r, c, v;
        cin >> r >> c >> v;
        --r, --c;
        grid[r][c] = v;
    }

    auto dp = vectors(-1LL, R, C, 4);
    dp[0][0][0] = 0;
    if (grid[0][0] != -1) dp[0][0][1] = grid[0][0];
    repeat(i, R) {
        repeat(j, C) {
            if (j - 1 >= 0) {
                repeat(k, 4) dp[i][j][k] = dp[i][j - 1][k];
                if (grid[i][j] != -1) {
                    repeat_from(k, 1, 4) {
                        if (dp[i][j - 1][k - 1] != -1)
                            setmax(dp[i][j][k], dp[i][j - 1][k - 1] + grid[i][j]);
                    }
                }
            }
            if (i - 1 >= 0) {
                repeat(k, 4) {
                    if (dp[i - 1][j][k] != -1) {
                        setmax(dp[i][j][0], dp[i - 1][j][k]);
                    }
                }
                if (grid[i][j] != -1) {
                    repeat(k, 4) {
                        if (dp[i - 1][j][k] != -1)
                            setmax(dp[i][j][1], dp[i - 1][j][k] + grid[i][j]);
                    }
                }
            }
        }
    }

    cout << *max_element(dp[R - 1][C - 1].begin(), dp[R - 1][C - 1].end()) << endl;
    return 0;
}