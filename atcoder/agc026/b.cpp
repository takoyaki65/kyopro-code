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

#define PRINT(X) cout << #X << " " << X << endl

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long A, B, C, D;
        cin >> A >> B >> C >> D;

        if (B > A or B > D) {
            cout << "No" << endl;
            continue;
        }

        if (C >= B) {
            cout << "Yes" << endl;
            continue;
        }
        assert((B <= A and B <= D and C < B));

        A %= B;
        long long g = __gcd(B, D);
        // A + k*D mod Bの最大値
        long long x = B - g + A % g;
        if (x > C) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}