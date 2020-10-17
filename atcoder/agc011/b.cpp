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
    vector<long long> A(N);
    repeat(i, N) cin >> A[i];
    sort(begin(A), end(A));
    vector<long long> S(N + 1);
    repeat(i, N) S[i + 1] = S[i] + A[i];
    /*
    repeat(i, N) cout << A[i] << " ";
    cout << endl;
    repeat(i, N + 1) cout << S[i] << " ";
    cout << endl;
     */
    vector<bool> survive(N);
    survive[N - 1] = true;
    int res = 0;
    int cur = N - 1;
    for (int i = N; i >= 1; --i) {
        while (cur >= i and A[cur] > 2 * S[i]) --cur;
        //cerr << "i : " << i << " cur: " << cur << endl;
        if (survive[cur]) {
            survive[i - 1] = true;
            ++res;
        }
    }
    cout << res << endl;
    return 0;
}