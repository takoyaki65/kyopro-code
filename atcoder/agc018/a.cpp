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

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    if (N == 1) {
        if (A[0] == K)
            cout << "POSSIBLE" << endl;
        else
            cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    int G = __gcd(A[0], A[1]);
    repeat_from(i, 2, N) {
        G = __gcd(G, A[i]);
    }

    int maxA = -10;
    for (int x : A) setmax(maxA, x);
    if (K % G == 0 and K <= maxA) {
        cout << "POSSIBLE" << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}