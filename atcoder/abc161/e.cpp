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
    int N, K, C;
    string S;
    cin >> N >> K >> C >> S;
    vector<int> L(N), R(N);
    {
        int prev = 10000000;
        int now = 1;
        int i = 0;
        while (now <= K and i < N) {
            if (S[i] == 'o' and prev > C) {
                prev = 0;
                L[i] = now++;
            }
            ++i;
            ++prev;
        }
    }
    {
        int prev = 10000000;
        int now = K;
        int i = N - 1;
        while (now > 0 and i >= 0) {
            if (S[i] == 'o' and prev > C) {
                prev = 0;
                R[i] = now--;
            }
            --i;
            ++prev;
        }
    }
    repeat(i, N) {
        if (L[i] != 0 and L[i] == R[i]) {
            cout << i + 1 << endl;
        }
    }
    return 0;
}