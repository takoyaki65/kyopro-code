#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T &x) {
    return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool setmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

// 1, 2, ... , N^2が要素 → 異なる操作をしたら必ず重複のない異なる行列になる？
// 一度swapした列をまた元に戻すようなことは考えない
//

int main() {
    set<vector<vector<int>>> res;
    vector<vector<int>> grid = {{3, 2, 7}, {4, 8, 9}, {1, 6, 5}};
    res.insert(grid);

    int K = 13;

    auto rec = [&res, &K](auto f, vector<vector<int>> &g) -> void {
        // 行
        repeat(i, 3) {
            repeat_from(j, i + 1, 3) {
                bool flg = true;
                repeat(k, 3) {
                    if (g[i][k] + g[j][k] > K) {
                        flg = false;
                        break;
                    }
                }
                if (!flg) continue;
                repeat(k, 3) swap(g[i][k], g[j][k]);
                if (res.count(g)) flg = false;
                res.insert(g);
                if (flg) f(f, g);
                repeat(k, 3) swap(g[i][k], g[j][k]);
            }
        }

        // 列
        repeat(i, 3) {
            repeat_from(j, i + 1, 3) {
                bool flg = true;
                repeat(k, 3) {
                    if (g[k][i] + g[k][j] > K) {
                        flg = false;
                        break;
                    }
                }
                if (!flg) continue;
                repeat(k, 3) swap(g[k][i], g[k][j]);
                if (res.count(g)) flg = false;
                res.insert(g);
                if (flg) f(f, g);
                repeat(k, 3) swap(g[k][i], g[k][j]);
            }
        }
    };
    rec(rec, grid);

    cout << res.size() << endl;
    cout << endl;
    for (auto &g : res) {
        repeat(i, 3) {
            repeat(j, 3) {
                cout << g[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}