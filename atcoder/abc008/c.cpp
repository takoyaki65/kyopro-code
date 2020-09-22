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

int main() {
    int N;
    cin >> N;
    vector<int> C(N);
    repeat(i, N) cin >> C[i];
    double res = 0.0;
    repeat(i, N) {
        // C[i]の約数の個数を調べる
        int S = 0;
        repeat(j, N) {
            if (i == j) continue;
            if (C[i] % C[j] == 0) {
                ++S;
            }
        }
        if (S % 2 == 0) {
            res += double(S + 2) / (2 * S + 2);
        } else {
            res += 1.0 / 2.0;
        }
    }
    cout << fixed << setprecision(10) << res << endl;
    return 0;
}