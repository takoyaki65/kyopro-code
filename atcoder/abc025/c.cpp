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

int score(int turn) {
    if (turn == 9) {
        int res = 0;
        repeat(i, 2) {
            repeat(j, 3) {
                if (board[i][j] == board[i + 1][j]) {
                    res += B[i][j];
                } else {
                    res -= B[i][j];
                }
            }
        }

        repeat(i, 3) {
            repeat(j, 2) {
                if (board[i][j] == board[i][j + 1]) {
                    res += C[i][j];
                } else {
                    res -= C[i][j];
                }
            }
        }
        return res;
    }

    if (turn % 2 == 0) {
        // 直大
        int res = int(-1e9);
        repeat(i, 3) {
            repeat(j, 3) {
                if (board[i][j] == -1) {
                    board[i][j] = 0;
                    setmax(res, score(turn + 1));
                    board[i][j] = -1;
                }
            }
        }
        return res;
    } else {
        // 直子
        int res = (int)1e9;
        repeat(i, 3) {
            repeat(j, 3) {
                if (board[i][j] == -1) {
                    board[i][j] = 1;
                    setmin(res, score(turn + 1));
                    board[i][j] = -1;
                }
            }
        }
        return res;
    }
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
    memset(board, -1, sizeof(board));

    int df = score(0);
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