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

const int mod = 1000000007;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    auto tbl = vectors(0, N + 1, 3);
    repeat(i, N) {
        vector<int> xyz = tbl[i];
        repeat(j, 3) {
            if (xyz[j] == A[i]) {
                ++xyz[j];
                break;
            }
        }
        sort(rbegin(xyz), rend(xyz));
        tbl[i + 1] = xyz;
    }

    long long res = 1;
    repeat(i, N) {
        int cnt = 0;
        repeat(j, 3) {
            if (tbl[i][j] == A[i]) ++cnt;
        }
        res = res * cnt % mod;
    }
    cout << res << endl;
    return 0;
}