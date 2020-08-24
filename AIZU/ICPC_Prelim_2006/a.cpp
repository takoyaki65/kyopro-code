#include <algorithm>
#include <cassert>
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
    const int MAX_N = 1000010;
    vector<bool> is_prime(MAX_N, true);
    is_prime[0] = is_prime[1] = false;
    repeat(i, MAX_N) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int a, d, n;
    while (cin >> a >> d >> n, a | d | n) {
        int cnt = 0;
        while (true) {
            assert(a < MAX_N);
            if (is_prime[a]) ++cnt;
            if (cnt >= n) break;
            a += d;
        }
        cout << a << endl;
    }
    return 0;
}