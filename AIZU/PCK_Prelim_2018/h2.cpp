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
    int N;
    cin >> N;
    auto C = vectors(-1, N, 0);
    repeat(i, N) {
        int M;
        cin >> M;
        C[i].resize(M);
        repeat(j, M) {
            cin >> C[i][j];
        }
    }
    multiset<int> se;

    long long res = 0;
    for (int i = N - 1; i >= 0; --i) {
        for (int x : C[i]) {
            se.insert(x);
        }
        auto max_itr = se.rbegin();
        res += *max_itr;
        auto rm_itr = se.find(*max_itr);
        if (rm_itr != se.end())
            se.erase(rm_itr);
    }
    cout << res << endl;
    return 0;
}