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
int sz(T &x) {
    return x.size();
}

template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T &a, T const &b) {
    if (a > b) a = b;
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

    vector<long long> acum(N + 1);
    repeat(i, N) acum[i + 1] = acum[i] + A[i];
    vector<long long> p_acum(N + 1);
    repeat(i, N) p_acum[i + 1] = p_acum[i] + max(A[i], 0);

    long long res = numeric_limits<long long>::min();
    repeat(i, N - K + 1) {
        // [i, i + K)
        long long score = max(0LL, acum[i + K] - acum[i]) +
                          (p_acum[i] - p_acum[0]) +
                          (p_acum[N] - p_acum[i + K]);
        setmax(res, score);
    }
    cout << res << endl;
    return 0;
}