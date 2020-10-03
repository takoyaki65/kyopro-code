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

int main() {
    long long N, A, B;
    cin >> N >> A >> B;
    if (A + B - 1 > N) {
        cout << -1 << endl;
        return 0;
    }
    if (1LL * A * B < N) {
        cout << -1 << endl;
        return 0;
    }

    long long cur = 1;
    long long sub = 1LL * A * B - N;
    while (A > 0) {
        long long k = B - min(B - 1LL, sub);
        repeat(i, k) {
            cout << cur + k - 1 - i << " ";
        }
        cur += k;
        sub -= min(B - 1, sub);
        --A;
    }
    cout << endl;
    return 0;
}