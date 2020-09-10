#include <algorithm>
#include <cmath>
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

int main() {
    string S, T;
    cin >> S >> T;
    int ans = T.size();
    for (int i = 0; i + T.size() - 1 < S.size(); ++i) {
        int tmp = 0;
        for (int j = 0; j < T.size(); ++j) {
            if (S[i + j] != T[j]) ++tmp;
        }
        setmin(ans, tmp);
    }
    cout << ans << endl;
    return 0;
}