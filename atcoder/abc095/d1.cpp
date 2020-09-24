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
    long long C;
    cin >> N >> C;
    vector<long long> x(N), v(N);
    repeat(i, N) cin >> x[i] >> v[i];
    vector<long long> AnOA(N + 1, 0LL);
    vector<long long> BnOB(N + 1, 0LL);
    repeat(i, N) {
        AnOA[i + 1] = AnOA[i] + v[i] - x[i];
        if (i - 1 >= 0) AnOA[i + 1] += x[i - 1];
    }
    repeat(i, N) {
        setmax(AnOA[i + 1], AnOA[i]);
    }
    for (int i = N - 1; i >= 0; --i) {
        BnOB[i] = BnOB[i + 1] + v[i] - (C - x[i]);
        if (i + 1 <= N - 1) BnOB[i] += C - x[i + 1];
    }
    for (int i = N - 1; i >= 0; --i) {
        setmax(BnOB[i], BnOB[i + 1]);
    }
    long long B = 0;
    long long OB = 0;
    long long res = numeric_limits<long long>::min();
    for (int i = N; i >= 0; --i) {
        if (i < N) {
            B += v[i];
            OB = C - x[i];
        }
        setmax(res, B - OB - OB + AnOA[i]);
    }
    long long A = 0;
    long long OA = 0;
    for (int i = 0; i <= N; ++i) {
        if (0 < i) {
            A += v[i - 1];
            OA = x[i - 1];
        }
        setmax(res, A - OA - OA + BnOB[i]);
    }
    cout << res << endl;
    return 0;
}