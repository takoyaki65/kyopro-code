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

int main() {
    int A, B, X;
    cin >> A >> B >> X;
    int res = 1000000000;
    for (int a = 0; a * 1000 <= X + 2000; ++a) {
        int b = 0;
        if (X >= a * 1000) {
            b = (X - a * 1000 + 499) / 500;
        }
        setmin(res, a * A + b * B);
    }
    cout << res << endl;
    return 0;
}