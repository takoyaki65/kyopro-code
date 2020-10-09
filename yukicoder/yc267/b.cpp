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

long long ll_pow(long long x, int n) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

long long factorial(long long x) {
    long long res = 1;
    while (x > 0) {
        res *= x;
        --x;
    }
    return res;
}

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    int maxA = -10, minA = 1000000010;
    repeat(i, N) {
        setmax(maxA, A[i]);
        setmin(minA, A[i]);
    }
    //cout << maxA << endl;
    //cout << minA << endl;
    if (maxA >= 4) {
        cout << 1000000007 << endl;
    } else if (minA == 0) {
        cout << -1 << endl;
    } else {
        long long res = 1;
        repeat(i, N) {
            res *= ll_pow(A[i], factorial(A[i]));
            if (1000000007 <= res) {
                cout << 1000000007 << endl;
                return 0;
            }
        }
        cout << 1000000007 % res << endl;
    }
    return 0;
}