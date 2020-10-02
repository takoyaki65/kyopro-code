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

bool validate(int N, int h, int n, int w) {
    return 4 * h * n * w == N * n * w + N * h * w + N * h * n;
}

int main() {
    long long N;
    cin >> N;
    for (long long h = 1; h <= 3500; ++h) {
        for (long long n = 1; n <= 3500; ++n) {
            if (4 * h * n - N * n - N * h == 0) continue;
            long long w = n * N * h / (4 * h * n - N * n - N * h);
            if (validate(N, h, n, w) && w > 0) {
                cout << h << " " << n << " " << w << endl;
                return 0;
            }
        }
    }
    return 0;
}