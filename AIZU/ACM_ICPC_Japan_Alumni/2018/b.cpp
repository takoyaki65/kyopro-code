#include <algorithm>
#include <cmath>
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
    int n, l, r;
    while (cin >> n >> l >> r, n | l | r) {
        vector<int> A(n);
        repeat(i, n) cin >> A[i];

        int res = 0;
        repeat_from(x, l, r + 1) {
            int cnt = 0;
            for (cnt = 0; cnt < n; ++cnt) {
                if (x % A[cnt] == 0) {
                    break;
                }
            }
            if (cnt % 2 == 0) {
                ++res;
            }
        }
        cout << res << endl;
    }
    return 0;
}