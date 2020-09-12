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
    int L, X, Y, S, D;
    cin >> L >> X >> Y >> S >> D;

    double res = __DBL_MAX__;
    // まっすぐ進むとき
    if (S > D) {
        assert(L - S + D >= 0 && X + Y >= 0);
        double tmp = double(L - S + D) / (X + Y);
        setmin(res, tmp);
    } else {
        assert(D - S >= 0 && X + Y >= 0);
        double tmp = double(D - S) / (X + Y);
        setmin(res, tmp);
    }
    // 逆進するとき
    if (X < Y) {
        if (S > D) {
            assert(S - D >= 0 && Y - X >= 0);
            double tmp = double(S - D) / (Y - X);
            setmin(res, tmp);
        } else {
            assert(S + L - D >= 0 && Y - X >= 0);
            double tmp = double(S + L - D) / (Y - X);
            setmin(res, tmp);
        }
    }
    cout << fixed << setprecision(10) << res << endl;
    return 0;
}