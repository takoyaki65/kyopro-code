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
#define sz(x) int(x.size())
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

const double pi = acos(-1);

// (101 * 100 / 2) ** 2 = (5050)**2 = 2.5 * 10^7

int main() {
    int h, w;
    cin >> h >> w;
    auto black = vectors(0, h, w);
    auto white = vectors(0, h, w);
    repeat(i, h) {
        repeat(j, w) {
            if ((i + j) % 2 == 0) {
                cin >> black[i][j];
            } else {
                cin >> white[i][j];
            }
        }
    }

    auto b_acum = vectors(0, h + 1, w + 1);
    auto w_acum = vectors(0, h + 1, w + 1);
    repeat(i, h) {
        repeat(j, w) {
            b_acum[i + 1][j + 1] = b_acum[i][j + 1] + b_acum[i + 1][j] - b_acum[i][j] + black[i][j];
            w_acum[i + 1][j + 1] = w_acum[i][j + 1] + w_acum[i + 1][j] - w_acum[i][j] + white[i][j];
        }
    }

    int res = 0;
    repeat_from(y1, 1, h + 1) {
        repeat_from(y2, 0, y1) {
            repeat_from(x1, 1, w + 1) {
                repeat_from(x2, 0, x1) {
                    // [y2, y1), [x2, x1)
                    int b = b_acum[y1][x1] - b_acum[y1][x2] - b_acum[y2][x1] + b_acum[y2][x2];
                    int w = w_acum[y1][x1] - w_acum[y1][x2] - w_acum[y2][x1] + w_acum[y2][x2];
                    if (b == w) {
                        setmax(res, (y1 - y2) * (x1 - x2));
                    }
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}