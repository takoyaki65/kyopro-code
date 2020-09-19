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

// たぶん周期性があるはず、ありそう
#define PRINT(X) cout << #X << " " << X << endl;

int main() {
    long long N, X, M;
    cin >> N >> X >> M;
    vector<bool> visited(M, false);
    vector<long long> B;
    long long Ai = X;
    while (!visited[Ai]) {
        visited[Ai] = true;
        Ai = (Ai * Ai) % M;
    }
    // Ai がループの最初
    long long loop_begin = Ai;
    //PRINT(loop_begin);
    Ai = X;
    while (Ai != loop_begin) {
        B.push_back(Ai);
        Ai = (Ai * Ai) % M;
    }
    vector<long long> vecLoop;
    Ai = loop_begin;
    while (true) {
        vecLoop.push_back(Ai);
        Ai = (Ai * Ai) % M;
        if (Ai == loop_begin) break;
    }

    /*     cout << "B: " << endl;
    for (int i = 0; i < B.size(); ++i) cout << B[i] << " -> ";
    cout << endl;
    cout << "loop_begin: " << endl;
    for (int i = 0; i < vecLoop.size(); ++i) cout << vecLoop[i] << " -> ";
    cout << endl;
    */
    // ループ手前
    long long p = B.size();
    long long psum = 0;
    for (long long x : B) psum += x;

    // ループ
    long long q = vecLoop.size();
    long long qsum = 0;
    for (long long x : vecLoop) qsum += x;

    /*
    PRINT(p);
    PRINT(q);
    */
    long long res = 0;
    if (N < p) {
        for (int i = 0; i < p; ++i) {
            res += B[i];
        }
        cout << res << endl;
    } else {
        res += psum;
        res += (N - p) / q * qsum;
        for (int i = 0; i < (N - p) % q; ++i) {
            res += vecLoop[i];
        }
        cout << res << endl;
    }

    return 0;
}