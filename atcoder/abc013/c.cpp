#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
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

// (N日すべての満足度の変化) + H > 0
// 各日について、満足度は0より大きくなければならない
// 食いだめした方が確実にN日過ごしやすい
// H + B*x + D*y - E(N - x - y) > 0
// y*(D + E) + H + B*x - E*N + E*x> 0
// y > (E*N - E*x - B*x - H)/(D + E)

int main() {
    long long N, H, A, B, C, D, E;
    cin >> N >> H >> A >> B >> C >> D >> E;
    long long res = numeric_limits<long long>::max();
    for (long long x = 0; x <= N; ++x) {
        int y = 0;
        if (E * (N - x) - B * x - H < 0)
            y = 0;
        else
            y = (E * (N - x) - B * x - H) / (D + E) + 1;
        if (x + y > N || y < 0) continue;
        setmin(res, A * x + C * y);
    }
    cout << res << endl;
    return 0;
}