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
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    long long res = -1000000000000000010LL;
    repeat(x_rev, 2) {
        repeat(y_rev, 2) {
            long long tmp = 0;
            if (x_rev)
                tmp = a;
            else
                tmp = b;
            if (y_rev)
                tmp *= c;
            else
                tmp *= d;
            setmax(res, tmp);
        }
    }
    cout << res << endl;
    return 0;
}