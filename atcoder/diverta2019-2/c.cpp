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

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    sort(A.begin(), A.end());
    vector<int> acum(N + 1);
    repeat(i, N) acum[i + 1] = acum[i] + A[i];
    int res = -1000000010;
    int k = 0;
    repeat_from(i, 1, N) {
        int tmp = (acum[N] - acum[i]) - (acum[i] - acum[0]);
        if (res < tmp) {
            res = tmp;
            k = i;
        }
    }
    cout << res << endl;
    int Minus = A[0];
    repeat(i, N - k - 1) {
        cout << Minus << " " << A[k + i] << endl;
        Minus -= A[k + i];
    }

    int Plus = A[N - 1];
    repeat(i, k - 1) {
        cout << Plus << " " << A[1 + i] << endl;
        Plus -= A[1 + i];
    }
    cout << Plus << " " << Minus << endl;
    return 0;
}