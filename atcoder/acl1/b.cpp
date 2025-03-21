#include <algorithm>
#include <atcoder/math>
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

void divisor(long long n, vector<long long> &res) {
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            res.push_back(i);
            if (i * i != n) res.push_back(n / i);
        }
    }
    sort(res.begin(), res.end());
    return;
}

int main() {
    long long N;
    cin >> N;
    vector<long long> div2N;
    divisor(2LL * N, div2N);
    long long res = 1e18;
    for (auto x : div2N) {
        auto pk = atcoder::crt({0, -1}, {x, 2LL * N / x});
        long long k = pk.first;
        if (k == 0) continue;
        setmin(res, k);
    }
    cout << res << endl;
    return 0;
}