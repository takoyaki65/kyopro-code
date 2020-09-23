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
    int N, M;
    cin >> N >> M;
    vector<long long> x(N), y(N), z(N);
    repeat(i, N) cin >> x[i] >> y[i] >> z[i];

    vector<long long> xyz(N);
    long long res = numeric_limits<long long>::lowest();
    for (int S = 0; S < (1 << 3); ++S) {
        for (int i = 0; i < N; ++i) {
            xyz[i] = ((S & 1) ? x[i] : -x[i]) + ((S >> 1) & 1 ? y[i] : -y[i]) + ((S >> 2) & 1 ? z[i] : -z[i]);
        }
        sort(xyz.rbegin(), xyz.rend());
        long long tmp = 0;
        for (int i = 0; i < M; ++i) {
            tmp += xyz[i];
        }
        setmax(res, tmp);
    }
    cout << res << endl;
    return 0;
}