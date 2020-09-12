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

// N = m * a + a = a * (m + 1)
// (0 <= a < m)

void divisor(long long n, vector<long long> &ret) {
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) ret.push_back(n / i);
        }
    }
    sort(ret.begin(), ret.end());
    return;
}

int main() {
    long long N;
    cin >> N;
    vector<long long> div_N_1;
    divisor(N - 1, div_N_1);

    vector<long long> div_N;
    divisor(N, div_N);

    long long res = div_N_1.size() - 1;
    for (int i = 1; i < div_N.size(); ++i) {
        long long tmp = N;
        while (tmp % div_N[i] == 0) tmp /= div_N[i];
        if (tmp % div_N[i] == 1) ++res;
    }
    cout << res << endl;
    return 0;
}