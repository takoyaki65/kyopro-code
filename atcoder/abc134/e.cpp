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

const int INF = 1e9 + 7;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    deque<int> deq;
    repeat(i, N) {
        int p = lower_bound(deq.begin(), deq.end(), A[i]) - deq.begin();
        if (p == 0) {
            deq.push_front(A[i]);
        } else {
            deq[p - 1] = A[i];
        }

        // for (int p : deq) {
        //     cout << p << " ";
        // }
        // cout << endl;
    }
    int ans = deq.size();
    cout << ans << endl;
    return 0;
}