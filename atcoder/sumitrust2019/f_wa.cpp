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
    long long T1, T2, A1, A2, B1, B2;
    cin >> T1 >> T2 >> A1 >> A2 >> B1 >> B2;
    long long K = T1 * (A1 - B1) + T2 * (A2 - B2);
    if (K == 0) {
        cout << "infinity" << endl;
        return 0;
    }
    long long res = 0;
    // (0, T1]
    if (A1 > B1) {
        long long D = T1 * (A1 - B1);
        if (K < 0) {
            res += D / (-K);
        }
    } else {
        long long D = T1 * (A1 - B1);
        if (K > 0) {
            res += (-D) / K;
        }
    }

    // (T1, T1 + T2]
    if (A2 > B2) {
        long long D = T2 * (A2 - B2);
        //cout << "D: " << D << endl;
        //cout << "K: " << K << endl;
        if (K > 0) {
            res += (D - K + K - 1) / K;
        }
    } else {
        long long D = T2 * (A2 - B2);
        if (K < 0) {
            res += (-(D - K + K - 1)) / (-K);
        }
    }
    cout << res << endl;
    return 0;
}