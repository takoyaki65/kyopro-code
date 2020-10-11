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

// Nが小さいから非効率なことができそう
// N^4は間に合わない

int main() {
    int N;
    cin >> N;
    vector<string> S(N);
    repeat(i, N) cin >> S[i];
    int res = 0;
    repeat(a, N) {
        vector<string> T = S;
        repeat(i, N) {
            repeat(j, N) {
                T[i][j] = S[(i + a) % N][j];
            }
        }
        bool flg = true;
        repeat(i, N) {
            repeat_from(j, i + 1, N) {
                if (T[i][j] != T[j][i]) {
                    flg = false;
                    break;
                }
            }
            if (!flg) break;
        }
        if (flg) res += N;
    }
    cout << res << endl;
    return 0;
}