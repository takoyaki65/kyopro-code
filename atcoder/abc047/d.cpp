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
    long long T;
    cin >> N >> T;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    vector<int> minA(N + 1, 1e9 + 7);
    repeat(i, N) {
        minA[i + 1] = min(minA[i], A[i]);
    }

    vector<int> B(N);
    repeat(i, N) {
        B[i] = A[i] - minA[i];
        //cout << B[i] << " ";
    }
    //cout << endl;

    int P = *max_element(B.begin(), B.end());
    int x = 0;
    for (int bi : B) {
        if (P == bi) ++x;
    }
    cout << x << endl;
    return 0;
}