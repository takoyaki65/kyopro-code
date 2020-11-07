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

// まず(N+1)人で二人ペア(N+1)/2個組んで、身長差の合計が最も小さくなる方法を模索

int main() {
    int N, M;
    cin >> N >> M;
    vector<long long> H(N), W(M);
    repeat(i, N) cin >> H[i];
    repeat(i, M) cin >> W[i];
    sort(begin(H), end(H));
    sort(begin(W), end(W));

    vector<long long> L(N + 1), R(N + 1);
    repeat(i, N) {
        if (i % 2) {
            assert(i - 1 >= 0);
            L[i] = abs(H[i] - H[i - 1]);
            if (i - 2 >= 0) L[i] += L[i - 2];
        } else {
            if (i - 1 >= 0) L[i] = L[i - 1];
        }
    }

    for (int i = N - 1; i >= 0; --i) {
        if (i % 2) {
            assert(i + 1 < N);
            R[i] = abs(H[i + 1] - H[i]);
            if (i + 2 < N) R[i] += R[i + 2];
        } else {
            if (i + 1 < N) R[i] = R[i + 1];
        }
    }

    long long res = 1e18;
    int cur = 0;
    for (int w : W) {
        while (cur + 1 <= N and H[cur] <= w) ++cur;
        // H配列のcur番目が直後にある場所に置く
        long long tmp = 0;
        tmp += (cur - 1 >= 0 ? L[cur - 1] : 0);
        tmp += (cur < N ? R[cur] : 0);
        if (cur % 2) {
            if (cur - 1 >= 0) {
                tmp += abs(w - H[cur - 1]);
            }
        } else {
            if (cur < N) {
                tmp += abs(w - H[cur]);
            }
        }
        setmin(res, tmp);
    }
    cout << res << endl;

    return 0;
}