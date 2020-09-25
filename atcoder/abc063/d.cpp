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
    long long B, A;
    cin >> N >> A >> B;
    vector<int> h(N);
    repeat(i, N) cin >> h[i];

    long long ng = 0, ok = 1e9 + 7;
    while (abs(ok - ng) > 1) {
        long long mid = ng + (ok - ng) / 2;
        //cout << "ng: " << ng << " mid: " << mid << " ok: " << ok << endl;
        // mid回攻撃を行う
        long long T = 0;
        repeat(i, N) {
            if (mid * B <= h[i]) {
                T += (h[i] - mid * B + A - B - 1) / (A - B);
            }
        }
        if (T <= mid) {
            ok = mid;
        } else {
            ng = mid;
        }
    }

    cout << ok << endl;
    return 0;
}