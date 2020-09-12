#include <algorithm>
#include <cmath>
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

int main() {
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, -1, 0, 1};

    auto A = vectors(0, 4, 4);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> A[i][j];
        }
    }

    repeat(i, 4) {
        repeat(x, 4) {
            repeat(y, 4) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
                if (A[x][y] == A[nx][ny]) {
                    cout << "CONTINUE" << endl;
                    return 0;
                }
            }
        }
    }
    cout << "GAMEOVER" << endl;
    return 0;
}