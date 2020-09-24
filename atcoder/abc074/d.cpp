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

template <class T>
using V = vector<T>;
template <class T>
using VV = V<V<T>>;

bool IsValid(VV<long long> &G) {
    int N = G.size();
    repeat(k, N) {
        repeat(i, N) {
            repeat(j, N) {
                if (G[i][j] > G[i][k] + G[k][j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int N;
    cin >> N;
    auto A = vectors(0LL, N, N);
    repeat(i, N) {
        repeat(j, N) {
            cin >> A[i][j];
        }
    }
    if (!IsValid(A)) {
        cout << -1 << endl;
    } else {
        long long res = 0;
        const int INF = 1e9 + 7;
        repeat(k, N) {
            repeat(i, N) {
                repeat(j, N) {
                    if (i == k || j == k) continue;
                    if (A[i][j] == A[i][k] + A[k][j]) {
                        A[i][j] = INF;
                    }
                }
            }
        }
        repeat(i, N) {
            repeat_from(j, 0, i) {
                if (A[i][j] != INF) {
                    res += A[i][j];
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}