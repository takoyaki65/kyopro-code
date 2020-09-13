#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
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
    cin >> N;
    vector<long long> x(N), y(N);
    repeat(i, N) {
        cin >> x[i] >> y[i];
    }
    vector<long long> fx(N), fy(N);
    repeat(i, N) {
        fx[i] = x[i] - y[i];
        fy[i] = x[i] + y[i];
    }
    long long res = -1;
    long long maxf = INT64_MIN, minf = INT64_MAX;
    for (int i = 0; i < N; ++i) {
        setmax(maxf, fx[i]);
        setmin(minf, fx[i]);
    }
    setmax(res, maxf - minf);
    maxf = INT64_MIN, minf = INT64_MAX;
    for (int i = 0; i < N; ++i) {
        setmax(maxf, fy[i]);
        setmin(minf, fy[i]);
    }
    setmax(res, maxf - minf);
    cout << res << endl;
    return 0;
}