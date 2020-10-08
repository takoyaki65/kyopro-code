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

int Query(int q) {
    cout << q << endl;
    string reply;
    cin >> reply;
    if (reply == "Vacant") {
        return -1;
    } else if (reply == "Male") {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int N;
    cin >> N;
    int L = 0, R = N - 1;
    int ls = 0, rs = 0;
    ls = Query(0);
    if (ls == -1) {
        return 0;
    }
    rs = Query(N - 1);
    if (rs == -1) {
        return 0;
    }
    int query = 18;
    while (query--) {
        int mid = (L + R) / 2;
        //cout << L << " " << mid << " " << R << endl;
        int res = Query(mid);
        if (res == -1) {
            return 0;
        }
        if ((mid - L) % 2 == 1) {
            if (ls == res) {
                R = mid;
                rs = res;
            } else {
                L = mid;
                ls = res;
            }
        } else {
            if (ls != res) {
                R = mid;
                rs = res;
            } else {
                L = mid;
                ls = res;
            }
        }
    }
    return 0;
}