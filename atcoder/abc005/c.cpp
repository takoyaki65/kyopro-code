#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
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

// 貪欲

int main() {
    int T, N, M;
    cin >> T >> N;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    cin >> M;
    vector<int> B(M);
    repeat(i, M) cin >> B[i];

    if (N < M) {
        //cout << "pe" << endl;
        cout << "no" << endl;
        return 0;
    }

    int r = 0;
    repeat(i, N) {
        if (r >= M) break;
        if (A[i] <= B[r] && B[r] <= A[i] + T) {
            ++r;
        }
    }

    if (r >= M) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}