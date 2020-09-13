#include <algorithm>
#include <cassert>
#include <cmath>
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

// 同じ数の整数がN+1個以上あると無理
// そうでないならうまくできそう
// 構築方法
// どれから決める? -> 使える場所が少ない数から決めていく

int main() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    repeat(i, N) cin >> A[i];
    repeat(i, N) cin >> B[i];
    map<int, vector<int>> vA, vB;
    repeat(i, N) {
        vA[A[i]].push_back(i);
        vB[B[i]].push_back(i);
    }

    return 0;
}