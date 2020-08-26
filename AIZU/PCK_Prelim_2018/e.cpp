#include <algorithm>
#include <cmath>
#include <iostream>
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

int keta(int x) {
    int res = 0;
    while (x > 0) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

long long pow2(long long x, int a) {
    long long res = 1;
    while (a > 0) {
        if (a & 1) res *= x;
        x *= x;
        a >>= 1;
    }
    return res;
}

int main() {
    long long a, n, m;
    cin >> a >> n >> m;
    int res = 0;
    for (long long y = 1; true; ++y) {
        long long x = pow2(y + a, n);
        if (x > m) break;
        if (y == keta(x)) ++res;
    }
    cout << res << endl;
    return 0;
}