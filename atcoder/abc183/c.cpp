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

int main() {
    int n, k;
    cin >> n >> k;
    auto t_vec = vectors(0, n, n);
    repeat(i, n) {
        repeat(j, n) {
            cin >> t_vec[i][j];
        }
    }

    vector<int> cmb(n-1);
    int res = 0;
    iota(cmb.begin(), cmb.end(), 1);
    do {
        int d = 0;
        for(int i = 1; i < n-1; ++i) {
            int u = cmb[i-1];
            int v = cmb[i];
            d += t_vec[u][v];
        }
        d += t_vec[0][cmb[0]] + t_vec[cmb[n-2]][0];
        if(d == k) ++res;
    } while(next_permutation(cmb.begin(), cmb.end()));
    cout << res << endl;
    return 0;
}