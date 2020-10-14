#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
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

int main() {
    int N;
    cin >> N;
    for (int K = 1; K * (K - 1) <= 2 * N; ++K) {
        if (K * (K - 1) == 2 * N) {
            cout << "Yes" << endl;
            cout << K << endl;
            int cur = 1;
            auto res = vectors(0, K, 0);
            repeat(i, K) res[i].reserve(K - 1);
            repeat_from(step, 1, K) {
                repeat(i, K) {
                    int j = i + step;
                    if (j >= K) break;
                    res[i].push_back(cur);
                    res[j].push_back(cur);
                    ++cur;
                }
            }

            repeat(i, K) {
                cout << K - 1 << " ";
                repeat(j, K - 1) {
                    cout << res[i][j] << (j == K - 2 ? '\n' : ' ');
                }
            }
            return 0;
        }
    }
    cout << "No" << endl;
    return 0;
}