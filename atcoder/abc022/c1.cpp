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

template <class T>
using V = vector<T>;

template <class T>
using VV = V<V<T>>;

using pii = pair<int, int>;
using pli = pair<long long, int>;

long long d[310];
const long long INF = 1e18;

int main() {
    int N, M;
    cin >> N >> M;
    auto G = vectors(INF, N, N);
    repeat(i, N) G[i][i] = 0;
    repeat(i, M) {
        int u, v, l;
        cin >> u >> v >> l;
        --u, --v;
        G[u][v] = G[v][u] = l;
    }

    repeat_from(k, 1, N) {
        repeat_from(i, 1, N) {
            repeat_from(j, 1, N) {
                setmin(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }

    long long res = INF;
    repeat_from(i, 1, N) {
        repeat_from(j, i + 1, N) {
            // 0 -> i -> j -> 0
            setmin(res, G[0][i] + G[i][j] + G[j][0]);
        }
    }
    cout << (res == INF ? -1 : res) << endl;

    return 0;
}