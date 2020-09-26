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
#define sz(x) int(x.size())
using namespace std;
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
    int N;
    long long K;
    cin >> N >> K;
    vector<int> A(N);
    vector<int> F(N);
    repeat(i, N) cin >> A[i];
    repeat(i, N) cin >> F[i];
    sort(A.begin(), A.end());
    sort(F.rbegin(), F.rend());

    auto f = [&](long long mid) -> bool {
        long long x = 0;
        repeat(i, N) {
            x += max(0LL, (long long)A[i] - mid / F[i]);
        }
        return x <= K;
    };

    long long ng = -1, ok = 1e12 + 1000;
    while (abs(ok - ng) > 1) {
        long long mid = ng + (ok - ng) / 2;
        if (f(mid))
            ok = mid;
        else
            ng = mid;
    }
    cout << ok << endl;
    return 0;
}