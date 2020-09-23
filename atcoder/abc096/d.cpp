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

const int MAX_M = 55560;

int main() {
    int N;
    cin >> N;
    vector<bool> is_prime(MAX_M, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i < MAX_M; ++i) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < MAX_M; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<int> res;
    int cur = 0;
    while (res.size() < N && cur < MAX_M) {
        while (!is_prime[cur]) cur++;
        if (cur % 5 == 1) {
            res.push_back(cur);
        }
        ++cur;
    }

    assert(res.size() == N);
    for (int i = 0; i < N; ++i) {
        cout << res[i] << endl;
    }
    return 0;
}