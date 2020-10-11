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
inline int sz(T &x) {
    return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool setmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

int main() {
    int N, K, Q;
    cin >> N >> K >> Q;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    int res = numeric_limits<int>::max();
    repeat(i, N) {
        int Y = A[i];
        //cout << "Y: " << Y << endl;
        int l = 0, r = 0;
        vector<int> B;
        B.reserve(N);
        while (l < N and r < N) {
            while (r < N and A[r] >= Y) ++r;
            //cout << "l: " << l << " r: " << r << endl;
            // [l, r)
            if (r - l >= K) {
                vector<int> v(r - l);
                v.assign(A.begin() + l, A.begin() + r);
                //cout << "v: " << endl;
                // for (int x : v) {
                //     //cout << x << endl;
                //     assert(x >= Y);
                // }
                sort(begin(v), end(v));
                repeat(j, r - l - K + 1) B.push_back(v[j]);
            }
            l = r + 1;
            r = l;
        }
        if (B.size() >= Q) {
            sort(begin(B), end(B));
            assert(B[0] >= A[i]);
            int X = B[Q - 1];
            //cout << "X: " << X << endl;
            setmin(res, X - Y);
        }
    }
    cout << res << endl;
    return 0;
}