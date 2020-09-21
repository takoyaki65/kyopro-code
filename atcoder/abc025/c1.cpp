#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
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

int board[3][3];
int B[2][3], C[3][2];
int dp[(1 << 9)][(1 << 9)];

int score(int turn, int a, int b) {
    if (turn == 9) {
        assert((a | b) == (1 << 9) - 1);
        int res = 0;
        repeat(i, 2) {
            repeat(j, 3) {
                int x = 1 << (3 * i + j);
                int y = 1 << (3 * (i + 1) + j);
                if (((x & a) and (y & a)) xor ((x & b) and (y & b))) {
                    res += B[i][j];
                } else {
                    res -= B[i][j];
                }
                x = 1 << (3 * j + i);
                y = 1 << (3 * j + (i + 1));
                if (((x & a) and (y & a)) xor ((x & b) and (y & b))) {
                    res += C[j][i];
                } else {
                    res -= C[j][i];
                }
            }
        }
        return dp[a][b] = res;
    }

    if (dp[a][b] != -1) {
        return dp[a][b];
    }

    int res = (turn % 2) ? 1e9 : -1e9;
    repeat(i, 3) {
        repeat(j, 3) {
            int x = 1 << (3 * i + j);
            if (not(x & a) and not(x & b)) {
                if (turn % 2) {
                    setmin(res, score(turn + 1, a, b | x));
                } else {
                    setmax(res, score(turn + 1, a | x, b));
                }
            }
        }
    }
    return dp[a][b] = res;
}

int main() {
    repeat(i, 2) {
        repeat(j, 3) {
            cin >> B[i][j];
        }
    }
    repeat(i, 3) {
        repeat(j, 2) {
            cin >> C[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));

    int df = score(0, 0, 0);
    //cout << "df: " << df << endl;
    // chokudai + chokuko = Bij と Cijの総和
    // chokudai - chokuko = df
    int sum = 0;
    repeat(i, 3) repeat(j, 2) sum += B[j][i] + C[i][j];
    int chokudai = (sum + df) / 2;
    int chokuko = (sum - df) / 2;
    cout << chokudai << endl;
    cout << chokuko << endl;

    return 0;
}