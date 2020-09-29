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

const double pi = acos(-1);

int main() {
    int n, q;
    cin >> n >> q;
    vector<double> S(20100, 0.0);
    repeat(i, n) {
        long long x, r, h;
        cin >> x >> r >> h;
        // [x, x + h)
        double All = pi * r * r * h / 3.0;
        repeat(j, h) {
            // All = 1/3 * r * r * pi * h
            // S[x + j] = All * (h - j)**3/h**3 - All * (h - j - 1)**3/h**3
            S[x + j] += All * ((h - j) * (h - j) * (h - j) - (h - j - 1) * (h - j - 1) * (h - j - 1)) / (h * h * h);
        }
    }
    repeat(i, 20000) {
        S[i + 1] += S[i];
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << fixed << setprecision(10) << S[b - 1] - S[a - 1] << endl;
    }
    return 0;
}