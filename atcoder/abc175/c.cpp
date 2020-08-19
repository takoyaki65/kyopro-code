#include <algorithm>
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

int main() {
    long long X, K, D;
    cin >> X >> K >> D;
    if (X < 0) X *= -1LL;
    long long K1 = K - X / D;
    if (K1 < 0) {
        cout << X - K * D << endl;
        return 0;
    }
    X %= D;
    if (K1 % 2 == 0) {
        cout << X << endl;
    } else {
        cout << abs(X - D) << endl;
    }
    return 0;
}