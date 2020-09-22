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
    int N, M;
    cin >> N >> M;
    vector<long long> V(M + 1);
    long long sum = 0;
    repeat(i, N) {
        int l, r, s;
        cin >> l >> r >> s;
        --l;
        V[l] += s;
        V[r] -= s;
        sum += s;
    }
    repeat_from(i, 1, M + 1) {
        V[i] = V[i] + V[i - 1];
    }
    cout << sum - *min_element(V.begin(), V.end() - 1) << endl;
    return 0;
}