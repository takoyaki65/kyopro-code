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

// 和は累積和を使って全列挙できるとして、
// K個の中からどのように選ぶか

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> a(N);
    repeat(i, N) cin >> a[i];
    int len = N * (N + 1) / 2;
    vector<long long> acum(N + 1);
    repeat(i, N) acum[i + 1] = acum[i] + a[i];
    vector<long long> x;
    repeat(i, N) {
        repeat_from(j, i + 1, N + 1) {
            x.push_back(acum[j] - acum[i]);
        }
    }
    assert(len == sz(x));
    long long res = 0;
    for (int bit = 40; bit >= 0; --bit) {
        int num = 0;
        long long nxt = res bitor (1LL << bit);
        repeat(i, len) {
            if ((nxt bitand x[i]) == nxt) ++num;
        }
        if (num >= K) res = nxt;
    }
    cout << res << endl;
    return 0;
}